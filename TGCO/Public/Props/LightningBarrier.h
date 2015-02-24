

#pragma once

#include "Props/Props.h"
#include "Props/LightningBarrierSkeletalMeshComp.h"
#include "LightningBarrier.generated.h"

/**
 * Class representing a lightning barrier. The lightning can be switched off
 * by the use of a @ref ALightningSwitch instance
 */

UCLASS()
class TGCO_API ALightningBarrier : public AProps
{
	GENERATED_BODY()

public:
	/** Constructors */
	ALightningBarrier(const FObjectInitializer& PCIP);

	UFUNCTION(BlueprintCallable, Category = "LightningBarrier")
		/**
		 * public  method : Change the active state (whether or not the lightning
		 * is active)
		 * @method:    ChangeActiveState
		 * @return:   void
		 */
		 void ChangeActiveState();

	/** Boolean describing the active state of the lightning. Can be edited in
	the unreal editor and have an immediate effect on the instance in the scene */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightningBarrier")
		bool bIsLightningActive;

	/** Mesh representing the barrier itself */
	UPROPERTY(EditAnywhere, Category = "LightningBarrier")
		ULightningBarrierSkeletalMeshComp * pBarrier;


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

protected:
};
