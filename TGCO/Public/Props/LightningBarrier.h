

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

	ALightningBarrier(const FObjectInitializer& ObjectInitializer);
	
	/**
	* public  method : Change the active state (whether or not the lightning
	* is active)
	* @method:    ChangeActiveState
	* @return:   void
	*/
	UFUNCTION(BlueprintCallable, Category = "LightningBarrier")
	void ChangeActiveState();

	UFUNCTION()
	void OnRep_LightningState();


	/** Boolean describing the active state of the lightning. Can be edited in
	the unreal editor and have an immediate effect on the instance in the scene */
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_LightningState, EditAnywhere, BlueprintReadOnly, Category = "LightningBarrier")
	bool bIsLightningActive;

	/** Mesh representing the barrier itself */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "LightningBarrier")
	ULightningBarrierSkeletalMeshComp * pBarrier;

	virtual void ChangeActiveStateFromServer(bool bValue);

	virtual void UpdateActiveState();

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
