

#pragma once
#include <vector>

#include "InteractiveElement/InteractiveElement.h"
#include "Props/LightningBarrier.h"
#include "LightningSwitch.generated.h"

/**
 * @brief Switch allowing the player to turn off a @ref ALightningBarrier (either a simple one
 * or part of a @ref AMultiLightningBarrier
 *
 * 	@sa AInteractiveElement
 */
UCLASS()
class TGCO_API ALightningSwitch : public AInteractiveElement
{

	GENERATED_BODY()

public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	ALightningSwitch(const FObjectInitializer& ObjectInitializer);

	/** Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "LightningSwitch")
		virtual bool OnInteract() override;

	/** Array containing pointers to all the barrier it controls */
	UPROPERTY(EditAnywhere, Category = "LightningSwitch")
		TArray<ALightningBarrier *> m_vControledTerminals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightningSwitch")
		TArray<UStaticMeshComponent *> Informers;



private:

};
