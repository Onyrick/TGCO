

#pragma once

#include "Components/SkeletalMeshComponent.h"
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

public:
	/** Mesh of the barrier's first pylon */
	UPROPERTY(EditAnywhere, Category = "LightningBarrier")
		UStaticMeshComponent * pFirstTerminalComponent;

	/** Mesh of the barrier's lightning */
	UPROPERTY(EditAnywhere, Category = "LightningBarrier")
		UStaticMeshComponent * pSecondTerminalComponent;

	/** Mesh of the barrier's second pylon */
	UPROPERTY(EditAnywhere, Category = "LightningBarrier")
		UStaticMeshComponent * pLightningComponent;

private:
};
