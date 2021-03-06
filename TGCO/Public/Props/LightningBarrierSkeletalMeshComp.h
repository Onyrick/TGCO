

#pragma once
#include "Components/SkeletalMeshComponent.h"
#include "Puzzle/BarrierColor.h"
#include "LightningBarrierSkeletalMeshComp.generated.h"


/**
 * @class ULightningBarrierSkeletalMeshComp
 *
 * @brief Class inherited from skeletal mesh component.
 * Used to create a lightning barrier mesh and keeping track of the
 * lightning state (on or off)
 */
UCLASS()
class TGCO_API ULightningBarrierSkeletalMeshComp : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	/* @brief Constructor */
	ULightningBarrierSkeletalMeshComp(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief Changes the state of the lightning.
	 *
	 * @param ActivateLightning New state for the light
	 */
	UFUNCTION(BlueprintCallable, Category = "LightningBarrier")
		void ChangeLightningState(bool ActivateLightning);

	/**
	* @brief Set the barrier material to give it an identifiable color.
	* This color is also found on the diodes of the different @ref LightningSwitch that 
	* control this barrier
	*
	* @param BarColor Color to apply to the barrier
	*/
	UFUNCTION(BlueprintCallable, Category = "LightningBarrier")
		void SetBarrierMaterial(EBarrierColor BarColor);

public:
	/** Mesh of the barrier's first pylon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightningBarrier")
		UStaticMeshComponent * pFirstTerminalComponent;

	/** Mesh of the barrier's lightning */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightningBarrier")
		UStaticMeshComponent * pSecondTerminalComponent;

	/** Mesh of the barrier's second pylon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightningBarrier")
		UStaticMeshComponent * pLightningComponent;

protected:
	
};
