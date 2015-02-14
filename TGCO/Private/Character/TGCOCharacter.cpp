// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TGCO.h"
#include "TGCOCharacter.h"
#include "Projectile.h"
#include "Engine.h"
#include "TGCOGameState.h"

#define COLLISION_HIGHLIGHT_TRACE ECC_GameTraceChannel1
#define COLLISION_INTERACTIVE_TRACE ECC_GameTraceChannel2

//////////////////////////////////////////////////////////////////////////
// ATGCOCharacter

ATGCOCharacter::ATGCOCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

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

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 400;

	bShootMode = true;
	WristMode = "STOP";
	WristModeIndex = 0;

	PreviousInteractiveElement = nullptr;
	iNumberOfCloseInteractiveElement = 0;

	PlayerPawn = nullptr;
	LastSpawn = nullptr;

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
	// if player is in FireMode
	if (bShootMode == true)
	{
		// try and fire a projectile
		if (ProjectileClass != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				// spawn the projectile at the muzzle
				AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
				Projectile->SetMode(WristMode);
			}
		}

		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != NULL)
		{
			/*
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != NULL)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
			*/
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
		
		if (ElementHit != NULL)
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
	ATGCOGameState * GS = Cast<ATGCOGameState>(GetWorld()->GetGameState());
	const TMap<int, FString>& UnlockSkills = GS->GetUnlockSkills();

	int lengthMap = UnlockSkills.Num();

	WristModeIndex = WristModeIndex - 1;
	if (WristModeIndex < 0)
	{
		WristModeIndex = lengthMap - 1;
	}

	WristMode = UnlockSkills[WristModeIndex];

	UE_LOG(LogDebug, Warning, TEXT("Previous : %s"), *WristMode);
}

void ATGCOCharacter::SetNextWristMode()
{
	ATGCOGameState * GS = Cast<ATGCOGameState>(GetWorld()->GetGameState());
	const TMap<int, FString>& UnlockSkills = GS->GetUnlockSkills();

	int lengthMap = UnlockSkills.Num();

	WristModeIndex = (WristModeIndex + 1) % lengthMap;

	WristMode = UnlockSkills[WristModeIndex];

	UE_LOG(LogDebug, Warning, TEXT("Next : %s"), *WristMode);
}

void ATGCOCharacter::CancelActionTime()
{
	ATGCOPlayerState * PS = Cast<ATGCOPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	PS->SetPropsAffected(NULL);

	UE_LOG(LogDebug, Warning, TEXT("Cancel action time"));
}

bool ATGCOCharacter::SetCheckpoint()
{
	FTransform ActorTransform = GetTransform();
	LastCheckpoint = ActorTransform;

	FVector vLocation = ActorTransform.GetLocation();

	return !vLocation.IsZero();
}

FTransform ATGCOCharacter::GetCheckpoint()
{
	return LastCheckpoint;
}

void ATGCOCharacter::SpawnPlayer()
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

	// Get the player controller
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		// Attach it to the new Character Pawn
		UE_LOG(LogDebug, Warning, TEXT("PLayerController possess now"));
		PC->Possess(PlayerPawn);
		Destroy();
	}
}

void ATGCOCharacter::KillPlayerThenRespawn()
{
	UE_LOG(LogDebug, Warning, TEXT("Kill Player and respawn"));

	//TODO : kill Player (Play animation etc..)
	DetachFromControllerPendingDestroy();
	SpawnPlayer();
}

void ATGCOCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (iNumberOfCloseInteractiveElement <= 0)
	{
		return;
	}
	
	HightlightCloseInteractiveElement();
}

void ATGCOCharacter::IncreaseNumberOfCloseInteractiveElement()
{
	iNumberOfCloseInteractiveElement++;
}

void ATGCOCharacter::DecreaseNumberOfCloseInteractiveElement()
{
	iNumberOfCloseInteractiveElement--;
}

void ATGCOCharacter::HightlightCloseInteractiveElement()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(false);

	bool hasHit = GetWorld()->LineTraceSingle(OutHitResult, GetActorLocation(), 3000.f*GetActorForwardVector(), COLLISION_HIGHLIGHT_TRACE, Params);

	if (hasHit)
	{
		AInteractiveElement* ElementHit = Cast<AInteractiveElement>(OutHitResult.GetActor());
		if (PreviousInteractiveElement != NULL && PreviousInteractiveElement != ElementHit)
		{
			PreviousInteractiveElement->Highlight(false);
			PreviousInteractiveElement = NULL;
		}
		if (ElementHit != NULL)
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
		if (PreviousInteractiveElement != NULL)
		{
			PreviousInteractiveElement->Highlight(false);
			PreviousInteractiveElement = NULL;
		}
	}
}

float ATGCOCharacter::TakeDamage(float fDamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		ATGCOGameState* GameState = Cast<ATGCOGameState>(World->GetGameState());
		if (GameState != NULL)
		{
			UE_LOG(LogDebug, Warning, TEXT("Player take damage"));
			// Active shield
			ActiveShield(true);

			// Decrease energy in the GameState
			if (GameState->DecreaseEnergy(fDamageAmount) == 0)
			{
				KillPlayerThenRespawn();
				return 0;
			}

			return fDamageAmount;
		}
	}

	return 0;
}

void ATGCOCharacter::ActiveShield(bool bActivate)
{
	if (bActivate)
	{
		UE_LOG(LogDebug, Warning, TEXT("Active Shield"));
		// Activate the shield
		PlayShieldAnimation();
		PlayShieldSound();
	}
	else
	{
		// TODO : Deactivate the shield
		// Need to do something ?
	}
}

void ATGCOCharacter::PlayShieldAnimation()
{
	// TODO
	UE_LOG(LogDebug, Warning, TEXT("TO DO : play activate shield animation"));
}

void ATGCOCharacter::PlayShieldSound()
{
	// TODO
	UE_LOG(LogDebug, Warning, TEXT("TO DO : play activate shield sound"));
}

UInventoryUMG* ATGCOCharacter::GetInventoryUMG()
{
	return InventoryUMG;
}

void ATGCOCharacter::SetInventoryUMG(UInventoryUMG* _widget)
{
	InventoryUMG = _widget;
}

void ATGCOCharacter::PickStockableItem(AStockable* _item)
{
	InventoryUMG->AddNewItem(_item);
	
}

void ATGCOCharacter::ToggleInventory()
{
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

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