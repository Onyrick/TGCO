// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster.h"
#include "FixBot.generated.h"

/**********************************************************************************************//**
* @brief	A specific type of monster, the Fixbot.
**************************************************************************************************/
UCLASS()
class TGCO_API AFixBot : public AMonster
{
	GENERATED_BODY()

public:
	AFixBot(const FObjectInitializer& ObjectInitializer);

	/**********************************************************************************************//**
	* @brief	Event launch when the MonstroPlante take damage.
	*
	* @param	DamageAmount		   	The damage amount.
	* @param	DamageEvent			   	The damage event.
	* @param 	EventInstigator	        If non-null, the event instigator.
	* @param 	DamageCauser   	        If non-null, the damage causer.
	*
	* @return	The damage actually applied.
	**************************************************************************************************/
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	/** @brief	The number of routes it can takes. */
	UPROPERTY(EditAnywhere, Category = Behavior)
	int32 MaxRoutes;
};
