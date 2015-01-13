// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "InteractiveElement.h"
#include "TGCOCharacter.generated.h"

UCLASS(config=Game)
class ATGCOCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;
	
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	ATGCOCharacter(const FObjectInitializer& ObjectInitializer);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Know if the player is in Shoot mode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool bShootMode; 

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;


protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** Called to augment max speed and allow player to run */
	void Run();

	/** Called to decrease max speed and disabled player to run */
	void StopRunning();

	/** Handler for firing */
	UFUNCTION()
	void OnFire();

public:
	/** Handler for using */
	UFUNCTION(BlueprintCallable, Category = "TGCOCharacter")
	void Use();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	//Tick
	virtual void Tick(float DeltaSeconds) override;

public:

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCameraComponent; }

	/** Function called when the Player receive damage from Elements in the World. Decrease Player's Energy and activate Shield.
	* @param DamageAmount How much damage to apply
	* @param DamageEvent Datapackage that fully describes the damage received
	* @param EventInvestigator The Controller responsible for the damage.
	* @param DamageCauser The Actor that directly caused the damage
	*
	* @return The amount of damage actually applied
	*/
	virtual float TakeDamage(float fDamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	void IncreaseNumberElement();
	void DecreaseNumberElement();

	bool IsInsideElevator();
	void SetInsideElevator();

private:

	/** Activates the protection of the Character. When active the Character can't die but loose some energy.
	* @param bActivate To active or deactivate the shield
	*/
	void ActiveShield(bool bActivate);

	/** Play the shield animation when the Player is taking damage */
	void PlayShieldAnimation();

	/** Play the shield sound when the Player is taking damage */
	void PlayShieldSound();

	AInteractiveElement* PreviousInteractiveElement; //Previous element which was highlighted
	int32 iNumberOfCloseInteractiveElement;
	bool bIsInsideElevator;
};

