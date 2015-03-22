// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterAI.h"
#include "Monster.generated.h"

/**
* @brief Define a movable monster which interact with the player
*/

UCLASS()
class TGCO_API AMonster : public ACharacterAI
{
	GENERATED_BODY()
public:
	AMonster(const FObjectInitializer& ObjectInitializer);

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
	* ### summary	Event launch when the Monster take damage.
	**************************************************************************************************/

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;


	/**********************************************************************************************//**
	 * @brief	Destroyed this object.
	 *
	 * ### summary	Event launched when the monster has to be destroyed.
	 **************************************************************************************************/

	virtual void Destroyed();


	/**********************************************************************************************//**
	 * @brief	Return wether the Monster is stunned.
	 *
	 * @return	true if stun, false if not.
	 **************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual bool IsStun();

	/**********************************************************************************************//**
	 * @brief	Stun this Monster.
	 *
	 * ### summary	Stun the Monster during a laps of time.
	 **************************************************************************************************/

	virtual void Stun();

	/**********************************************************************************************//**
	 * @brief	Unstun this Monster.
	 **************************************************************************************************/

	virtual void UnStun();


	/**********************************************************************************************//**
	 * @brief	Return wether the Monster is dead.
	 *
	 * @return	true if dead, false if not.
	 **************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual bool IsDead();

	/**********************************************************************************************//**
	 * @brief	Play a move sound when the Monster move.
	 **************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual void PlayMoveSound();

	/**********************************************************************************************//**
	 * @brief	Play a move animation when the Monster move.
	 **************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual void PlayMoveAnimation();

	/**********************************************************************************************//**
	 * @brief	Getter for the walk speed.
	 *
	 * @return	The walk speed.
	 **************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual float GetWalkSpeed();

	/**********************************************************************************************//**
	 * @brief	Setter for the walk speed.
	 *
	 * @param	_speed	The speed to set.
	 **************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual void SetWalkSpeed(float _speed);

	/** @brief	Respawn the current Monster. */
	virtual void RespawnAI();

	/**********************************************************************************************//**
	 * @brief	Allow or forbid the monster to move. For instance.
	 *
	 * @param	_ready	value to set.
	 **************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Monster")
	void SetReadyToMove(bool _ready);

	/**********************************************************************************************//**
	 * @brief	check if this monster is ready to move.
	 *
	 * @return	true if ready to move, false if not.
	 **************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Monster")
	bool isReadyToMove();

protected:

	/** @brief	Whether the Monster is stunned or not. */
	bool bIsStun;

	/** @brief	The time the Monster stay stunned. */
	float fStunTime;

	/** @brief The time before the Monster respawn */
	float fRespawnTime;
	/** Whether the Monster is dead or not */
	bool bIsDead;
	/** @brief Whether the Monster has to move */
	UPROPERTY(Transient, Replicated)
	bool bReadyToMove;
};
