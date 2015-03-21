// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "InteractiveElement.h"
#include "Stockable.h"
#include "InventoryUMG.h"
#include "ShootMode.h"
#include "SolutionType.h"
#include "TGCOCharacter.generated.h"

/** @brief	Represent a Character (Pawn) for a Player. */
UCLASS(config = Game)
class ATGCOCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	ATGCOCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	/**
	 * @brief	Sets up the player input component.
	 *
	 * @param 	InputComponent	If non-null, the input component.
	 *
	 * ### summary	Set up gameplay key binding.
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/**
	 * @brief	Handler for when a touch input started.
	 *
	 * @param	FingerIndex	Zero-based index of the finger.
	 * @param	Location   	The location.
	 */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/**
	 * @brief	Handler for when a touch input stopped.
	 *
	 * @param	FingerIndex	Zero-based index of the finger.
	 * @param	Location   	The location.
	 */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** @brief   Called to augment max speed and allow player to run */
	void Run();

	/** @brief   Called to decrease max speed and disabled player to run */
	void StopRunning();

	/**
	 * @brief	Called via input to turn at a given rate.
	 *
	 * @param	Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate.
	 */
	void TurnAtRate(float Rate);

	/**
	 * @brief	Called via input to turn look up/down at a given rate.
	 *
	 * @param	Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate.
	 */
	void LookUpAtRate(float Rate);

	/**
	 * @brief	Move forward.
	 *
	 * @param	Value	The value.
	 */
	void MoveForward(float Value);

	/**
	 * @brief	Move right.
	 *
	 * @param	Value	The value.
	 */
	void MoveRight(float Value);

	/** @brief	Executes the fire action. */
	UFUNCTION()
	void OnFire();

	/** @brief	Sets previous wrist mode. */
	void SetPreviousWristMode();

	/** @brief	Sets next wrist mode. */
	void SetNextWristMode();

	/** @brief   Cancel Action on the Props that is affected by time because of Projectile Shoot */
	void CancelActionTime();

public:	

	/** @brief	Handler for using an InteractiveElement of the World. */
	UFUNCTION(BlueprintCallable, Category = "TGCOCharacter")
	void Use();

	/**
	 * @brief	Sets the checkpoint.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */
	bool SetCheckpoint();

	/**
	 * @brief	Gets the checkpoint.
	 *
	 * @return	The checkpoint.
	 */
	FTransform GetCheckpoint() const;

	/**
	 * @brief	Spawn player to the last checkpoint.
	 *
	 * @return	A const new Character for the Player.
	 */
	ATGCOCharacter* const SpawnPlayer();

	/**
	 * @brief	Function called when the Player receive damage from Elements in the World. Decrease
	 * 			Player's Energy and activate Shield.
	 *
	 * @param	fDamageAmount		   	How much damage to apply.
	 * @param	DamageEvent			   	Datapackage that fully describes the damage received.
	 * @param 	EventInstigator	The Controller responsible for the damage.
	 * @param 	DamageCauser   	The Actor that directly caused the damage.
	 *
	 * @return	The amount of damage actually applied.
	 */
	virtual float TakeDamage(float fDamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	/** @brief	Increase number of close interactive element. */
	void IncreaseNumberOfCloseInteractiveElement();

	/** @brief	Decrease number of close interactive element. */
	void DecreaseNumberOfCloseInteractiveElement();

	/**
	 * @brief	Picks the stockable item described by _item.
	 *
	 * @param 	_item	If non-null, the item.
	 */
	void PickStockableItem(AStockable* _item);

	/**
	 * @brief	Gets inventory umg.
	 *
	 * @return	null if it fails, else the inventory umg.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UInventoryUMG* GetInventoryUMG() const;

	/**
	 * @brief	Sets inventory umg.
	 *
	 * @param 	_widget	If non-null, the widget.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetInventoryUMG(UInventoryUMG* _widget);

	/**
	* @brief	Gets HUD energy umg.
	*
	* @return	null if it fails, else the HUD energy umg.
	*/
	UFUNCTION(BlueprintCallable, Category = "HUD")
	UUserWidget* GetHUDEnergyUMG() const;

	/**
	* @brief	Sets HUD energy umg.
	*
	* @param 	_widget	If non-null, the widget.
	*/
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetHUDEnergyUMG(UUserWidget* _widget);

	/**
	 * @brief	Gets solution type.
	 *
	 * @return	The solution type.
	 */
	UFUNCTION(BlueprintCallable, Category = "SolutionType")
	ESolutionType::Type GetSolutionType();

	/**
	 * @brief	Sets solution type.
	 *
	 * @param	_solution	The solution.
	 */
	UFUNCTION(BlueprintCallable, Category = "SolutionType")
	void SetSolutionType(ESolutionType::Type _solution);

	/**
	 * @brief	Gets wrist mode.
	 *
	 * @return	The wrist mode.
	 */
	EShootMode::Type GetWristMode();

	/** @brief	Toggle inventory visibility. */
	void ToggleInventory();

	/** @brief Change the visibility of the HUD */
	void SetHUDVisibility(bool _visible);

protected:
	/**
	 * @brief	Ticks.
	 *
	 * @param	DeltaSeconds	The seconds elapsed since the last called.
	 */
	virtual void Tick(float DeltaSeconds) override;

	/**
	 * @brief	Active shield.
	 *
	 * @param	bActivate	true to activate.
	 */
	void ActiveShield(bool bActivate);

	/** @brief   Play the shield animation when the Player is taking damage */
	void PlayShieldAnimation();

	/** @brief   Play the shield sound when the Player is taking damage */
	void PlayShieldSound();

	/** @brief	Highlight close interactive element Character look at. */
	void HighlightCloseInteractiveElement();

public:

	/** @brief	A skeletal mesh component*. (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** @brief	A camera component*. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** @brief   Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** @brief   Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;
	
	/** @brief	The shield component*. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Shield)
	class UStaticMeshComponent* Shield;

	/** @brief  Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	/** @brief   Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	/** @brief  Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** @brief   AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

protected:
	/** @brief	The previous interactive element highlighted. */
	AInteractiveElement* PreviousInteractiveElement;
	/** @brief	Number of close interactive elements. */
	int32 iNumberOfCloseInteractiveElement;
	/** @brief	The last checkpoint. */
	FTransform LastCheckpoint;
	/** @brief	The last spawn. */
	APlayerStart* LastSpawn;
	/** @brief	The player pawn. */
	ATGCOCharacter* PlayerPawn;
	/** @brief	The wrist mode. */
	EShootMode::Type WristMode;
	/** @brief	Zero-based index of the wrist mode. */
	int WristModeIndex;
	/** @brief	The inventory umg. */
	UInventoryUMG* InventoryUMG;
	/** @brief	The HUD of the player with energy and shoot mode umg. */
	UUserWidget* HUDEnergyUMG;
	/** @brief	Type of the solution owned. */
	TEnumAsByte<ESolutionType::Type> SolutionType;
	/** @brief	The last regen time. */
	float fLastRegenTime;
	/** @brief	true if Player is protect. */
	bool bIsProtect;
	/** @brief	The time since protection is active. */
	float fTimeSinceProtectionIsActive;

public:
	/** @brief   Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	/** @brief   Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCameraComponent; }
};

