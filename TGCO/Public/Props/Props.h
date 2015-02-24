// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Props.generated.h"

/**
 * TODO
 */
UCLASS()
class TGCO_API AProps : public AActor
{
	GENERATED_BODY()
	
public:
	/** Constructors */
	AProps(const FObjectInitializer& ObjectInitializer);
	
	/** TODO */
	virtual UStaticMeshComponent* getStaticMesh();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	virtual void ReinitSpeed();

	void UpdateSpeedValue(float fNewSpeed);

	UFUNCTION()
	void OnRep_Speed();

	virtual void UpdateSpeed();

public: 
	/** TODO */
	UPROPERTY(EditAnywhere, Category = PropsComponents)
	UStaticMeshComponent* StaticMeshProps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
	float fInitialSpeed;

	UPROPERTY(Transient, ReplicatedUsing=OnRep_Speed, EditAnywhere, BlueprintReadWrite, Category = Speed)
	float fSpeed;

};
