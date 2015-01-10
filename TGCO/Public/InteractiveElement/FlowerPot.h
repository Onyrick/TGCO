

#pragma once

#include "InteractiveElement/InteractiveElement.h"
#include "FlowerPot.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API AFlowerPot : public AInteractiveElement
{
	GENERATED_BODY()
	
		//Constructors
		AFlowerPot(const FObjectInitializer& PCIP);

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Method called when the player wants to use the object
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "FlowerPot")
	virtual bool OnInteract() override;

protected:	
};
