// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterAI.h"
#include "Monster.generated.h"

/**
 *	TODO
 */
UCLASS()
class TGCO_API AMonster : public ACharacterAI
{
	GENERATED_UCLASS_BODY()
public:
	/** Event launch when the Monster take damage */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	/** Event launched when the monster has to be destroyed */
	virtual void Destroyed();

	/** Return wether the Monster is stunned */
	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual bool IsStun();
	
	/** Stun the Monster during a laps of time */
	//UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual void Stun();

	/** Unstun the Monster */
	//UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual void UnStun();

	/** Move the actor to a location */
	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual EPathFollowingRequestResult::Type MoveToLocation(const FVector & Dest);// const FVector & Dest, float AcceptanceRadius, bool bStopOnOverlap, bool bUsePathfinding, bool bProjectDestinationToNavigation, bool bCanStrafe, TSubclassOf< class UNavigationQueryFilter > FilterClass);

	/** Play a move sound when the Monster move */
	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual void PlayMoveSound();

	/** Play a move animation when the Monster move */
	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual void PlayMoveAnimation();
	
	/** Getter / Setter / Is */
	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual float GetWalkSpeed();

	UFUNCTION(BlueprintCallable, Category = "Monster")
	virtual void SetWalkSpeed(float _speed);

	virtual void RespawnAI();

protected:
	/** Whether the Monster is stunned or not */
	bool bIsStun;
	/** The time the Monster stay stunned */
	float fStunTime;
	/** The time before the Monster respawn */
	float fRespawnTime;
};
