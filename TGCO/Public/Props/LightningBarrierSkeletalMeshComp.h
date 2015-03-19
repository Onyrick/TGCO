

#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "LightningBarrierSkeletalMeshComp.generated.h"

/**
 * Class inherited from skeletal mesh component.
 * Used to create a lightning barrier mesh and keeping track of the
 * lightning state (on or off)
 */
UCLASS()
class TGCO_API ULightningBarrierSkeletalMeshComp : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	/* Constructors */
	ULightningBarrierSkeletalMeshComp(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "LightningBarrier")
		/**
		 * public method : Changes the state of the lightning.
		 * @method: ChangeLightningState
		 * @param:  bool ActivateLightning
		 * @return: void
		 */
		 void ChangeLightningState(bool ActivateLightning);

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
