// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "InteractiveElement.h"
#include "Stockable.h"
#include "InventoryUMG.h"
#include "ShootMode.h"
#include "SolutionType.h"
#include "TGCOCharacter.generated.h"

/**
 * Represent a Character for a Player
 * 
 */
UCLASS(config=Game)
class ATGCOCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Constructors */
	ATGCOCharacter(const FObjectInitializer& ObjectInitializer);

/// BEGIN INPUT ///
protected:
	/** APawn interface */
	/** Set up gameplay key binding */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	/** End of APawn interface */

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** Called to augment max speed and allow player to run */
	void Run();

	/** Called to decrease max speed and disabled player to run */
	void StopRunning();

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

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Handler for firing */
	UFUNCTION()
	void OnFire();

	/** Switch Wrist Mode to the previous mode in the Enumeration */
	void SetPreviousWristMode();

	/** Switch Wrist Mode to the previous mode in the Enumeration */
	void SetNextWristMode();

	/** Cancel Action on the Props that is affected by time because of Projectile Shoot */
	void CancelActionTime();

public:	
	/** Handler for using an InteractiveElement of the World */
	UFUNCTION(BlueprintCallable, Category = "TGCOCharacter")
	void Use();

/// END INPUT ///

	/** Set a checkpoint for re spawn */
	bool SetCheckpoint();
	/** Get the checkpoint for re spawn */
	FTransform GetCheckpoint() const;
	/** Spawn the Player to the last checkpoint */
	ATGCOCharacter* const SpawnPlayer();

	/** Function called when the Player receive damage from Elements in the World. Decrease Player's Energy and activate Shield.
	* @param DamageAmount How much damage to apply
	* @param DamageEvent Datapackage that fully describes the damage received
	* @param EventInvestigator The Controller responsible for the damage.
	* @param DamageCauser The Actor that directly caused the damage
	*
	* @return The amount of damage actually applied
	*/
	virtual float TakeDamage(float fDamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	/** Increase the iNumberOfCloseInteractiveElement */
	void IncreaseNumberOfCloseInteractiveElement();
	/** Decrease the iNumberOfCloseInteractiveElement */
	void DecreaseNumberOfCloseInteractiveElement();

	/** Function to add a stockable item in the inventory*/
	void PickStockableItem(AStockable* _item);

	/**Getter / Setter */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UInventoryUMG* GetInventoryUMG() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetInventoryUMG(UInventoryUMG* _widget);

	/** Toggle the visibility of the mouse and of the widget */
	void ToggleInventory();

	UFUNCTION(BlueprintCallable, Category = "SolutionType")
	ESolutionType::Type GetSolutionType();

	UFUNCTION(BlueprintCallable, Category = "SolutionType")
	void SetSolutionType(ESolutionType::Type _solution);

protected:
	/** Tick function */
	virtual void Tick(float DeltaSeconds) override;

	/** Activates the protection of the Character. When active the Character can't die but loose some energy.
	* @param bActivate To active or deactivate the shield
	*/
	void ActiveShield(bool bActivate);

	/** Play the shield animation when the Player is taking damage */
	void PlayShieldAnimation();

	/** Play the shield sound when the Player is taking damage */
	void PlayShieldSound();

	/** Highlight the InteractiveElement that the Character look */
	void HightlightCloseInteractiveElement();

// PUBLIC MEMBER
public:
	/** Pawn mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

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

// PRIVATE MEMBER
protected:
	/** Previous element which was highlighted */
	AInteractiveElement* PreviousInteractiveElement;
	/** Number of InteractiveElement that the Player can use in their perimeter */
	int32 iNumberOfCloseInteractiveElement;
	/** Last Character checkpoint */
	FTransform LastCheckpoint;
	/** Character PlayerStart */
	APlayerStart* LastSpawn;
	/** Character Pawn */
	ATGCOCharacter* PlayerPawn;
	/** Wrist Mode for Shoot */
	EShootMode::Type WristMode;
	/** Index of ShootMode in Enum */
	int WristModeIndex;
	/** The UMG Inventory */
	UInventoryUMG* InventoryUMG;
	/** Solution Type owned by the Player */
	TEnumAsByte<ESolutionType::Type> SolutionType;
	/** Last time when Player Regen */
	float fLastRegenTime;

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCameraComponent; }
};

