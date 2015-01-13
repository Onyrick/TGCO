

#pragma once

#include "InteractiveElement/InteractiveElement.h"
#include "Props/Tree.h"
#include "InteractiveElement/Seed.h"
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
	
	UPROPERTY(VisibleAnywhere, Category = "Tree")
		UCapsuleComponent* TreeCapsuleOverlapCheck;

	UPROPERTY(EditAnywhere, Category = "FlowerPot")
		UTree* TreeTrunc;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FBindableEvent_TreeVisible
		);

	/** Called when Server Search is finished */
	UPROPERTY(BlueprintAssignable, Category = "Tree")
		FBindableEvent_TreeVisible TreeVisible;

protected:	
	void GrowTree();
	void PlantSeed(ASeed * Seed);
	ASeed * RemoveSeed();
	ASeed * SwapSeed(ASeed * Seed);

private:
	ASeed * PlantedSeed;
};
