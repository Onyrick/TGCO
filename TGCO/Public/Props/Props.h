// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Props.generated.h"

/**
 * Props is an Actor that can be affect by Players shoot. 
 * When affects Props changes its fCurrentSpeed variable.
 * It is a replicated actor, changing must be done on server and replicate on client.
 */
UCLASS()
class TGCO_API AProps : public AActor
{
	GENERATED_BODY()
	
public:
	/** Constructors */
	AProps(const FObjectInitializer& ObjectInitializer);
	
	/** 
	 * Get the StaticMeshComponent 
	 *
	 * @return	StaticMeshProps 
	 */
	virtual UStaticMeshComponent* getStaticMesh();

	/** 
	 * Function call when Player's Projectile hit the Props
	 * Change the Props's fCurrentSpeed value according to the EShootMode::Type of the Projectile
	 * Then call UpdateSpeedValue function
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	/** Reinitialize fSpeed value to fInitialSpeed */
	virtual void ReinitSpeed();

	/**
	 * Update the fSpeed value according to fNewSpeed parameter
	 * Only the server can update fCurrentSpeed for replication
	 * When called on client, this function calls a server function on its PlayerController
	 *
	 * @param	fNewSpeed	Th new speed for this Props
	 */
	void UpdateSpeedValue(float fNewSpeed);

	/** Function call when the Props's fCurrentSpeed parameter is change by the server on the client */
	UFUNCTION()
	void OnRep_Speed();

	/** Unimplemented function, should be implemented in child class */
	virtual void UpdateSpeed();

public: 
	/** The static mesh of this Actor */
	UPROPERTY(EditAnywhere, Category = PropsComponents)
	UStaticMeshComponent* StaticMeshProps;

	/** The initial speed of Props */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
	float fInitialSpeed;

	/** The current speed of Props */
	UPROPERTY(Transient, ReplicatedUsing=OnRep_Speed, EditAnywhere, BlueprintReadWrite, Category = Speed)
	float fCurrentSpeed;

};
