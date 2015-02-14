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
	AProps(const FObjectInitializer& PCIP);
	
	/** TODO */
	virtual UStaticMeshComponent* getStaticMesh();

	float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	void ReinitSpeed();

public: 
	/** TODO */
	UPROPERTY(EditAnywhere, Category = "PropsComponents")
	UStaticMeshComponent* StaticMeshProps;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float initialSpeed;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float speed;

};
