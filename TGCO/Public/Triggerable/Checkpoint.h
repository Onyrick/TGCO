
#pragma once

#include "Triggerable/Triggerable.h"
#include "Checkpoint.generated.h"

/**
* @class ACheckpoint
* 		 
* @brief A checkpoint to save progression of the player. Automatically saved when the player pass throught the checkpoint.
* 
* @sa ATrigerrable		 
*/
UCLASS()
class TGCO_API ACheckpoint : public ATriggerable
{
	GENERATED_BODY()

public:
	ACheckpoint(const FObjectInitializer& ObjectInitializer);

	/**   
	* @brief Event launch when Player begin to trigger the TriggerBox component.
	*/
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	/**   
	* @brief Event launch when Player end to trigger the TriggerBox component. 
	*/
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};
