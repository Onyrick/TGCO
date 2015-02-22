

#pragma once

#include "Props/Props.h"
#include <Props/LightningBarrier.h>

#include "MultiLightningBarrier.generated.h"

/**
 * Inherits from @ref ALightningBarrier. Represents a barrier with multiple
 * lightning barrier on top of one another. Each LightningBarrier can be controlled
 * by a different @ref ALightningSwitch
 */

UCLASS()
class TGCO_API AMultiLightningBarrier : public ALightningBarrier
{
	GENERATED_BODY()
public:
	/** Constructors */
	AMultiLightningBarrier(const FObjectInitializer& PCIP);

	/**
	 * virtual public  method : Called when the user has deleted the item in the unreal
	 * editor, ie during edition time (as opposed to during runtime).
	 * @method:    ReceiveDestroyed
	 * @return:   void
	 */
	virtual void ReceiveDestroyed() override;

	/** Number of barrier that the multi barrier must hold */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MultiLightningBarrier")
		int32 iNbBarriers;

	/** Array containing all the @ref ALigthningBarrier composing the instance */
	UPROPERTY(EditAnywhere, Category = "MultiLightningBarrier")
		TArray<ALightningBarrier * > m_vBarriers;




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
