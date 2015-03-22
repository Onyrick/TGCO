
#pragma once

#include "GameFramework/Actor.h"
#include "Triggerable.generated.h"

/**
 * @brief Class that represent a triggerable actor of the World. 
 * Do not implement directly this class in Blueprint.
 */
UCLASS()
class TGCO_API ATriggerable : public AActor
{
	GENERATED_BODY()

public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	ATriggerable(const FObjectInitializer& ObjectInitializer);

	/** @brief Event launch when Player begin to trigger the TriggerBox component. */
	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	/** @brief Event launch when Player end to trigger the TriggerBox component. */
	UFUNCTION()
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	/** The trigger component to launch Overlapping event */
	UPROPERTY(EditAnywhere, Category = "Triggers")
	UBoxComponent* TriggerBox;

	/** The static mesh representing the Actor in the World */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	UStaticMeshComponent* StaticMesh;
};
