// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ControllerAI.h"
#include "CharacterAI.generated.h"

/**
 * @brief Define the main properties of a Character Artificial Intelligence
 */
UCLASS()
class TGCO_API ACharacterAI : public ACharacter
{
	GENERATED_BODY()
public:
	/** Constructors */
	ACharacterAI(const FObjectInitializer& ObjectInitializer);

	/**********************************************************************************************//**
	 * @brief	Function to get the AIController.
	 *
	 * @return	null if cast fails, else a controller AI.
	 **************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "CharacterAI")
	virtual AControllerAI* GetAIController();
	
	/** @brief	Event launch when the CharacterAI has to be destroyed. */
	UFUNCTION(BlueprintCallable, Category = "CharacterAI")
	virtual void Destroyed();

	/** @brief	Respawn the CharacterAI. */
	virtual void RespawnAI();

	/**********************************************************************************************//**
	 * @brief	Take damage.
	 *
	 * @param	DamageAmount		   	The damage amount.
	 * @param	DamageEvent			   	The damage event.
	 * @param 	EventInstigator	        If non-null, the event instigator.
	 * @param 	DamageCauser   	        If non-null, the damage causer.
	 *
	 * @return	The damage actually applied.
	 *
	 * ### summary	Event launch when the CharacterAI take damage.
	 **************************************************************************************************/

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	/**********************************************************************************************//**
	 * @brief	Receive actor begin overlap.
	 *
	 * @param	OtherActor	If non-null, the other actor.
	 *
	 * ### summary	Event launch when the CharacterAI is hit by another actor.
	 **************************************************************************************************/

	virtual void ReceiveActorBeginOverlap(AActor* OtherActor) override;

	/** @brief	The static mesh. */
	UPROPERTY(EditAnywhere, Category = "Static Meshes")
	UStaticMeshComponent* StaticMesh;

	/** @brief	A behavior tree, containing all the actions the AI takes according to the situation . */
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

	/**********************************************************************************************//**
	 * @brief	Face rotation.
	 *
	 * @param	NewRotation	The new rotation.
	 * @param	DeltaTime  	The delta time.
	 *
	 * ### summary	Function to make the character face a direction.
	 **************************************************************************************************/

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) override;

protected:
	/** @brief	A collision capsule response container. */
	FCollisionResponseContainer CapsuleResponseContainer;
};
