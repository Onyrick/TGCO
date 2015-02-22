

#pragma once
#include <vector>

#include "InteractiveElement/InteractiveElement.h"
#include "Props/LightningBarrier.h"
#include "LightningSwitch.generated.h"

/**
 * Switch allowing the player to turn off a @ref ALightningBarrier (either a simple one
 * or part of a @ref AMultiLightningBarrier 
 */
UCLASS()
class TGCO_API ALightningSwitch : public AInteractiveElement
{
	
	GENERATED_BODY()

public:
	/** Constructors */
	ALightningSwitch(const FObjectInitializer& PCIP);

	/** Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "LightningSwitch")
	virtual bool OnInteract() override;
	
	/** Array containing pointers to all the barrier it controls */
	UPROPERTY(EditAnywhere, Category = "LightningSwitch")
	TArray<ALightningBarrier * > m_vControledTerminals;


private:

};
