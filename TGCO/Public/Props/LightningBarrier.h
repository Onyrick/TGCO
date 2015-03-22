

#pragma once

#include "Props/Props.h"
#include "Props/LightningBarrierSkeletalMeshComp.h"
#include "LightningBarrier.generated.h"

/**
 *  @class ALightningBarrier
 *  	   
 * 	@brief Class representing a lightning barrier. The lightning can be switched off
 * by the use of a @ref ALightningSwitch instance
 */

UCLASS()
class TGCO_API ALightningBarrier : public AProps
{
	GENERATED_BODY()

public:
	/** @brief Constructor */
	ALightningBarrier(const FObjectInitializer& ObjectInitializer);
	
	/**
	* @brief Change the active state (whether or not the lightning
	* is active)
	*/
	UFUNCTION(BlueprintCallable, Category = "LightningBarrier")
	void ChangeActiveState();

	/**
	* @brief Function automatically called when @ref bIsLightningActive is replicated
	*/
	UFUNCTION()
	void OnRep_LightningState();

	/**
	* TODO
	*/
	virtual void ChangeActiveStateFromServer(bool bValue);

	/**
	* TODO
	*/
	virtual void UpdateActiveState();

public:
	/** Boolean describing the active state of the lightning. Can be edited in
	the unreal editor and have an immediate effect on the instance in the scene */
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_LightningState, EditAnywhere, BlueprintReadOnly, Category = "LightningBarrier")
	bool bIsLightningActive;

	/** Mesh representing the barrier itself */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "LightningBarrier")
	ULightningBarrierSkeletalMeshComp * pBarrier;

#if WITH_EDITOR
	/**
	 * @brief Method catching property changes event coming from the
	 * unreal editor. This is used to apply the changes during the scene edition to the
	 * modified instance (as opposed to during runtime)
	 * 
	 * @param FPropertyChangedEvent & PropertyChangedEvent
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
#endif

protected:
};
