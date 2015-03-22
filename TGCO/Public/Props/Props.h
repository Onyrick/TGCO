
#pragma once

#include "GameFramework/Actor.h"
#include "Props.generated.h"

/**
 * @brief	Props is an Actor that can be affect by Players shoot. When affects Props changes its
 * 			fCurrentSpeed variable. It is a replicated actor, changing must be done on server and
 * 			replicate on client.
 */
UCLASS()
class TGCO_API AProps : public AActor
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	AProps(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief	Get the StaticMeshComponent.
	 *
	 * @return	StaticMeshProps.
	 */
	virtual UStaticMeshComponent* GetStaticMesh();

	/**
	 * @brief	Function call when Player's Projectile hit the Props.
	 * 			Change the Props's fCurrentSpeed value according to the EShootMode::Type of the Projectile.
	 * 			Then call UpdateSpeedValue function.
	 *
	 * @param	fDamageAmount		   	How much damage to apply.
	 * @param	DamageEvent			   	Datapackage that fully describes the damage received.
	 * @param 	EventInstigator	The Controller responsible for the damage.
	 * @param 	DamageCauser   	The Actor that directly caused the damage.
	 *
	 * @return	The amount of damage actually applied.
	 */
	virtual float TakeDamage(float fDamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	/** @brief	Reinitialises the speed to initial speed. */
	virtual void ReinitSpeedToInitialSpeed();

	/**
	 * @brief	Update the fSpeed value according to fNewSpeed parameter.
	 * 			Only the server can update fCurrentSpeed for replication. 
	 * 			When called on client, this function calls a server function on its PlayerController.
	 *
	 * @param	fNewSpeed	Th new speed for this Props.
	 */
	void UpdateSpeedValue(float fNewSpeed);

	/**
	 * @brief	Function call when the Props's fCurrentSpeed parameter is change by the server on the
	 * 			client.
	 */
	UFUNCTION()
	void OnRep_Speed();

	/** @brief	Updates the speed components. Should be implemented in child class. */
	virtual void UpdateSpeedComponents();

public: 
	/** @brief	The static mesh for this Props. */
	UPROPERTY(EditAnywhere, Category = PropsComponents)
	UStaticMeshComponent* StaticMeshProps;

	/** @brief	The initial speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed)
	float fInitialSpeed;

	/** @brief	The current speed. */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_Speed, EditAnywhere, BlueprintReadWrite, Category = Speed)
	float fCurrentSpeed;
};
