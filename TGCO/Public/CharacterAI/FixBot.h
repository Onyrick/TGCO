// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster.h"
#include "FixBot.generated.h"

/**
 *	TODO
 */
UCLASS()
class TGCO_API AFixBot : public AMonster
{
	GENERATED_UCLASS_BODY()

public:
	/** Event launch when the FixBot take damage */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UPROPERTY(EditAnywhere, Category = Behavior)
	int32 MaxRoutes;
};
