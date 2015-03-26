

#pragma once

#include "Props/Props.h"
#include <Props/LightningBarrier.h>

#include "MultiLightningBarrier.generated.h"

/**
 * @class AMultiLightningBarrier
 * 		  
 * @brief Inherits from @ref ALightningBarrier. Represents a barrier with multiple
 * lightning barrier on top of one another. Each LightningBarrier can be controlled
 * by one or more different @ref ALightningSwitch
 */

UCLASS()
class TGCO_API AMultiLightningBarrier : public ALightningBarrier
{
	GENERATED_BODY()
public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	AMultiLightningBarrier(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief Called when the user has deleted the item in the unreal
	 * editor, ie during edition time (as opposed to during runtime).
	 */
	virtual void ReceiveDestroyed() override;

public:
	/** Number of barrier that the multi barrier must hold */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "MultiLightningBarrier")
		int32 iNbBarriers;

	/** Array containing all the @ref ALigthningBarrier composing the instance */
	UPROPERTY(Replicated, EditAnywhere, Category = "MultiLightningBarrier")
		TArray<ALightningBarrier * > aBarriers;

#if WITH_EDITOR
	/**
	* virtual public  method : Method catching property changes event coming from the
	* unreal editor. This is used to apply the changes during the scene edition to the
	* modified instance (as opposed to during runtime)
	* @method:    PostEditChangeProperty
	* @param: FPropertyChangedEvent & PropertyChangedEvent
	* @return:   void
	*/
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
private:
};
