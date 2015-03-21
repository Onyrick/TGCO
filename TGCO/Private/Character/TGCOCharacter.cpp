// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TGCO.h"
#include "TGCOCharacter.h"
#include "Projectile.h"
#include "Engine.h"
#include "TGCOPlayerState.h"
#include "TGCOGameState.h"
#include "TGCOGameMode.h"

#define COLLISION_HIGHLIGHT_TRACE ECC_GameTraceChannel1
#define COLLISION_INTERACTIVE_TRACE ECC_GameTraceChannel2

//////////////////////////////////////////////////////////////////////////
// ATGCOCharacter

ATGCOCharacter::ATGCOCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, BaseTurnRate(45.f)
, BaseLookUpRate(45.f)
, PreviousInteractiveElement(nullptr)
, iNumberOfCloseInteractiveElement(0)
, LastSpawn(nullptr)
, PlayerPawn(nullptr)
, WristMode(EShootMode::STOP)
, WristModeIndex(0)
, SolutionType(ESolutionType::NONE)
, fLastRegenTime(0.f)
, bIsProtect(false)
, fTimeSinceProtectionIsActive(0.f)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->RelativeLocation = FVector(0.f, 0.f, -150.f);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Shield component
	Shield = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Shield"));
	Shield->AttachParent = FirstPersonCameraComponent;
	Shield->SetVisibility(false);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 400;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATGCOCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ATGCOCharacter::OnFire);
	InputComponent->BindAction("Use", IE_Pressed, this, &ATGCOCharacter::Use);

	InputComponent->BindAction("Inventory", IE_Pressed, this, &ATGCOCharacter::ToggleInventory);

	InputComponent->BindAction("Run", IE_Pressed, this, &ATGCOCharacter::Run);
	InputComponent->BindAction("Run", IE_Released, this, &ATGCOCharacter::StopRunning);

	InputComponent->BindAction("SwitchModeUp", IE_Pressed, this, &ATGCOCharacter::SetPreviousWristMode);
	InputComponent->BindAction("SwitchModeDown", IE_Pressed, this, &ATGCOCharacter::SetNextWristMode);

	InputComponent->BindAction("Cancel", IE_Pressed, this, &ATGCOCharacter::CancelActionTime);

	InputComponent->BindAxis("MoveForward", this, &ATGCOCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATGCOCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ATGCOCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ATGCOCharacter::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &ATGCOCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ATGCOCharacter::TouchStopped);
}

void ATGCOCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void ATGCOCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void ATGCOCharacter::Run()
{
	GetCharacterMovement()->MaxWalkSpeed = 700;
}

void ATGCOCharacter::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

void ATGCOCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATGCOCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATGCOCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATGCOCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ATGCOCharacter::OnFire()
{
	ATGCOPlayerState* PlayerState = Cast<ATGCOPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	if (PlayerState)
	{
		if (PlayerState->eCurrentState == EPlayerStatus::IN_GAME)
		{
			ATGCOGameState* GameState = Cast<ATGCOGameState>(GetWorld()->GetGameState());
			if (GameState != nullptr && GameState->GetEnergy() > 20)
			{
				GameState->DecreaseEnergy(20);

				// try and fire a projectile
				if (ProjectileClass != nullptr)
				{
					const FRotator SpawnRotation = GetControlRotation();
					// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
					const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

					UWorld* const World = GetWorld();
					if (World != nullptr)
					{
						// spawn the projectile at the muzzle
						AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
						if (Projectile != nullptr)
						{
							Projectile->SetSolutionType(SolutionType);
							Projectile->SetMode(WristMode);
						}
					}
				}

				// try and play the sound if specified
				if (FireSound != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
				}

				// try and play a firing animation if specified
				if (FireAnimation != nullptr)
				{
					/*
					// Get the animation object for the arms mesh
					UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
					if (AnimInstance != nullptr)
					{
					AnimInstance->Montage_Play(FireAnimation, 1.f);
					}
					*/
				}
			}
		}
	}

	
}

void ATGCOCharacter::Use()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(false);
	
	// If raytracer hit an Actor
	bool hasHit = GetWorld()->LineTraceSingle(OutHitResult, GetActorLocation(), 3000.f*GetActorForwardVector(), COLLISION_INTERACTIVE_TRACE, Params);

	if (hasHit)
	{
		// Get the hitting element as an InteractiveElement
		AInteractiveElement* ElementHit = Cast<AInteractiveElement>(OutHitResult.GetActor());
		
		if (ElementHit != nullptr)
		{
			// If element is active
			if (ElementHit->IsInteractive())
			{
				UE_LOG(LogDebug, Warning, TEXT("%s : call the oninteract"), *ElementHit->GetActorClass()->GetName());
				ElementHit->OnInteract();
			}
		}					
	}
	else
	{
		//TODO : PlaySound "Nothing to Use"
	}
}

void ATGCOCharacter::SetPreviousWristMode()
{
	ATGCOPlayerState* PlayerState = Cast<ATGCOPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	if (PlayerState != nullptr)
	{
		if (PlayerState->eCurrentState == EPlayerStatus::IN_GAME)
		{
			ATGCOGameState * GameState = Cast<ATGCOGameState>(GetWorld()->GetGameState());
			if (GameState != nullptr)
			{
				const TMap<int, EShootMode::Type>& UnlockSkills = GameState->GetUnlockSkills();

				int lengthMap = UnlockSkills.Num();

				WristModeIndex = WristModeIndex - 1;
				if (WristModeIndex < 0)
				{
					WristModeIndex = lengthMap - 1;
				}

				WristMode = UnlockSkills[WristModeIndex];
			}			
		}
	}
}

void ATGCOCharacter::SetNextWristMode()
{
	ATGCOPlayerState* PlayerState = Cast<ATGCOPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	if (PlayerState != nullptr)
	{
		if (PlayerState->eCurrentState == EPlayerStatus::IN_GAME)
		{
			ATGCOGameState * GameState = Cast<ATGCOGameState>(GetWorld()->GetGameState());
			if (GameState != nullptr)
			{
				const TMap<int, EShootMode::Type>& UnlockSkills = GameState->GetUnlockSkills();

				int lengthMap = UnlockSkills.Num();

				WristModeIndex = (WristModeIndex + 1) % lengthMap;

				WristMode = UnlockSkills[WristModeIndex];
			}
		}
	}
}

void ATGCOCharacter::CancelActionTime()
{
	ATGCOPlayerState* PlayerState = Cast<ATGCOPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	if (PlayerState != nullptr)
	{
		PlayerState->SetPropsAffected(nullptr);
		PlayerState->SetModUsed(EShootMode::NONE);
	}

	UE_LOG(LogDebug, Warning, TEXT("Cancel action time"));
}

bool ATGCOCharacter::SetCheckpoint()
{
	FTransform ActorTransform = GetTransform();
	LastCheckpoint = ActorTransform;

	FVector vLocation = ActorTransform.GetLocation();

	return !vLocation.IsZero();
}

FTransform ATGCOCharacter::GetCheckpoint() const
{
	return LastCheckpoint;
}

ATGCOCharacter* const ATGCOCharacter::SpawnPlayer()
{
	UE_LOG(LogDebug, Warning, TEXT("Spawn Player"));
	FVector vLocation = LastCheckpoint.GetLocation();
	
	if (vLocation.IsZero())
	{
		UE_LOG(LogDebug, Warning, TEXT("No checkpoint found"));
		// We should not pass here because player can't die before having a checkpoint
		// Just in case spawn actor at the right Player Start
		// Can be simplify later if needed
		TArray<AActor*> OutPlayerStartActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), OutPlayerStartActors);
		for (auto OutPlayerStartActor : OutPlayerStartActors)
		{
			APlayerStart* PlayerStartActor = Cast<APlayerStart>(OutPlayerStartActor);
			if (PlayerStartActor)
			{
				LastSpawn = PlayerStartActor;
				break;
			}
		}

		// Spawn a new character to the location needed
		FTransform SpawnTransform = LastSpawn->GetTransform();
		PlayerPawn = GetWorld()->SpawnActor<ATGCOCharacter>(this->GetClass(), SpawnTransform.GetLocation(), SpawnTransform.Rotator());
	}
	else
	{
		UE_LOG(LogDebug, Warning, TEXT("Checkpoint found"));
		// Spawn a new character to the location needed
		PlayerPawn = GetWorld()->SpawnActor<ATGCOCharacter>(this->GetClass(), LastCheckpoint.GetLocation(), LastCheckpoint.Rotator());
		// Set this Player the current checkpoint 
		PlayerPawn->LastCheckpoint = this->LastCheckpoint;
	}
	return PlayerPawn;
}

void ATGCOCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		ATGCOGameState* GameState = Cast<ATGCOGameState>(World->GetGameState());
		if (GameState != nullptr)
		{	
			float fGameTime = World->GetTimeSeconds();
			if (fGameTime - fLastRegenTime >= 1.f)
			{
				fLastRegenTime = fGameTime;
				GameState->ManagePlayersEnergy();
			}
				
			// Need to test also if player has taken damages
			if (GameState->CheckRemainingEnergy() == false)
			{
				//GameMode is only on the server
				ATGCOGameMode* GameMode = Cast<ATGCOGameMode>(World->GetAuthGameMode());
				if (GameMode)
				{
					GameMode->ServerKillPlayersThenRespawn();
				}
			}

			// Check for protection 
			if (fGameTime - fTimeSinceProtectionIsActive >= 5.f && bIsProtect)
			{
				ActiveShield(false);
			}
		}
	}

	if (iNumberOfCloseInteractiveElement > 0)
	{
		HighlightCloseInteractiveElement();
	}
}

void ATGCOCharacter::IncreaseNumberOfCloseInteractiveElement()
{
	iNumberOfCloseInteractiveElement++;
}

void ATGCOCharacter::DecreaseNumberOfCloseInteractiveElement()
{
	iNumberOfCloseInteractiveElement--;
}

void ATGCOCharacter::HighlightCloseInteractiveElement()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(false);

	bool hasHit = GetWorld()->LineTraceSingle(OutHitResult, GetActorLocation(), 3000.f*GetActorForwardVector(), COLLISION_HIGHLIGHT_TRACE, Params);

	if (hasHit)
	{
		AInteractiveElement* ElementHit = Cast<AInteractiveElement>(OutHitResult.GetActor());
		if (PreviousInteractiveElement != nullptr && PreviousInteractiveElement != ElementHit)
		{
			PreviousInteractiveElement->Highlight(false);
			PreviousInteractiveElement = nullptr;
		}
		if (ElementHit != nullptr)
		{
			if (ElementHit->IsInteractive())
			{
				ElementHit->Highlight(true);
				PreviousInteractiveElement = ElementHit;
			}
			else
			{
				UE_LOG(LogDebug, Warning, TEXT("Element is not yet interactible"));
			}
		}
	}
	else
	{
		if (PreviousInteractiveElement != nullptr)
		{
			PreviousInteractiveElement->Highlight(false);
			PreviousInteractiveElement = nullptr;
		}
	}
}

float ATGCOCharacter::TakeDamage(float fDamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		ATGCOGameState* GameState = Cast<ATGCOGameState>(World->GetGameState());
		if (GameState != nullptr)
		{
			// Active shield
			if (!bIsProtect)
			{
				ActiveShield(true);
			}
			else
			{
				// If shield is activate, decrease less energy (because we are protected) !
				fDamageAmount *= 0.7f;
			}

			// Decrease energy in the GameState
			GameState->DecreaseEnergy(fDamageAmount, true);

			return fDamageAmount;
		}
	}

	return 0;
}

void ATGCOCharacter::ActiveShield(bool bActivate)
{
	if (bActivate == false)
	{
		UE_LOG(LogDebug, Warning, TEXT("Desactive shield"));
		Shield->SetVisibility(false);
	}
	else
	{
		UE_LOG(LogDebug, Warning, TEXT("Activate shield"));
		Shield->SetVisibility(true);
	}

	bIsProtect = bActivate;

	if (bActivate)
	{
		// Activate the shield
		PlayShieldAnimation();
		PlayShieldSound();

		UWorld * const World = GetWorld();
		if (World != nullptr)
		{
			fTimeSinceProtectionIsActive = World->GetTimeSeconds();
		}
	}
}

void ATGCOCharacter::PlayShieldAnimation()
{
	// TODO
}

void ATGCOCharacter::PlayShieldSound()
{
	// TODO
}

UInventoryUMG* ATGCOCharacter::GetInventoryUMG() const
{
	return InventoryUMG;
}

void ATGCOCharacter::SetInventoryUMG(UInventoryUMG* _widget)
{
	check(_widget);
	InventoryUMG = _widget;
}

UUserWidget* ATGCOCharacter::GetHUDEnergyUMG() const
{
	return HUDEnergyUMG;
}

void ATGCOCharacter::SetHUDEnergyUMG(UUserWidget* _widget)
{
	check(_widget);
	HUDEnergyUMG = _widget;
}

void ATGCOCharacter::PickStockableItem(AStockable* _item)
{
	check(_item);
	InventoryUMG->AddNewItem(_item);
	UWorld* World = GetWorld();
	if (World)
	{
		ATGCOPlayerState* PlayerState = Cast<ATGCOPlayerState>(World->GetFirstPlayerController()->PlayerState);
		if (PlayerState != nullptr)
		{
			PlayerState->AddNewInventoryItem(_item);
		}
	}

}

void ATGCOCharacter::ToggleInventory()
{
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
	if (MyController != nullptr)
	{
		if (InventoryUMG->IsVisible())
		{
			InventoryUMG->SetVisibility(ESlateVisibility::Hidden);
			MyController->bShowMouseCursor = false;
		}
		else
		{
			InventoryUMG->SetVisibility(ESlateVisibility::Visible);
			MyController->bShowMouseCursor = true;
		}
	}
}

void ATGCOCharacter::SetHUDVisibility(bool _visible)
{
	if (_visible)
	{
		HUDEnergyUMG->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogOnline, Log, TEXT("Change HUD to be visible"));
	}
	else
	{
		HUDEnergyUMG->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogOnline, Log, TEXT("Change HUD to be hidden"));
	}
}

ESolutionType::Type ATGCOCharacter::GetSolutionType()
{
	return SolutionType;
}

void ATGCOCharacter::SetSolutionType(ESolutionType::Type _solution)
{
	SolutionType = _solution;
}

EShootMode::Type ATGCOCharacter::GetWristMode()
{
	return WristMode;
}
