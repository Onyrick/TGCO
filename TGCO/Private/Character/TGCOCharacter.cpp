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

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 200;

	// Create a CameraComponent	
	FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CharacterMesh1P"));
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->RelativeLocation = FVector(0.f, 0.f, -150.f);

	bShootMode = false;

	PreviousInteractiveElement = NULL;
	iNumberOfCloseInteractiveElement = 0;

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

	InputComponent->BindAction("Run", IE_Pressed, this, &ATGCOCharacter::Run);
	InputComponent->BindAction("Run", IE_Released, this, &ATGCOCharacter::StopRunning);

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
	GetCharacterMovement()->MaxWalkSpeed = 500;
}

void ATGCOCharacter::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 200;
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
	if ((Controller != NULL) && (Value != 0.0f))
	{

		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATGCOCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
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
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, TEXT("Shoot"));
			}

			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				// spawn the projectile at the muzzle
				World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
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
	
	bool hasHit = GetWorld()->LineTraceSingle(OutHitResult, GetActorLocation(), 3000.f*GetActorForwardVector(), COLLISION_INTERACTIVE_TRACE, Params);

	if (hasHit)
	{
		AInteractiveElement* ElementHit = Cast<AInteractiveElement>(OutHitResult.GetActor());
		if (ElementHit != NULL)
		{
			if (ElementHit->IsInteractive())
			{
				ElementHit->OnInteract();
			}
		}					
	}
	else
	{
		//PlaySound "Nothing to Use"
	}
}

void ATGCOCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (iNumberOfCloseInteractiveElement <= 0)
		return;

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

void ATGCOCharacter::IncreaseNumberElement()
{
	iNumberOfCloseInteractiveElement++;
}

void ATGCOCharacter::DecreaseNumberElement()
{
	iNumberOfCloseInteractiveElement--;
}

float ATGCOCharacter::TakeDamage(float fDamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		ATGCOGameState* GameState = Cast<ATGCOGameState>(World->GetGameState());
		if (GameState != NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, TEXT("Take damage"));
			// Active shield
			ActiveShield(true);

			// Decrease energy in the GameState
			GameState->DecreaseEnergy(fDamageAmount);

			return fDamageAmount;
		}
	}

	return 0;
}

void ATGCOCharacter::ActiveShield(bool bActivate)
{
	if (bActivate)
	{
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, TEXT("Active Shield"));
		// Activate the shield
		PlayShieldAnimation();
		PlayShieldSound();
	}
	else
	{
		// Deactivate the shield
		// Need to do something ?
	}
}

void ATGCOCharacter::PlayShieldAnimation()
{
	// TO DO
	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, TEXT("TO DO : play activate shield animation"));
}

void ATGCOCharacter::PlayShieldSound()
{
	// TO DO
	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, TEXT("TO DO : play activate shield sound"));

}