
#pragma once

#include "InteractiveElement/InteractiveElement.h"
#include "Props/Tree.h"
#include "InteractiveElement/Seed.h"
#include "FlowerPot.generated.h"

/**
 * @brief A flower pot where player can plant a seed to make a tree grow
 * 	
 * 	@sa AInteractiveElement
 */
UCLASS()
class TGCO_API AFlowerPot : public AInteractiveElement
{
	GENERATED_BODY()

public:
	/** @brief Constructor */
	AFlowerPot(const FObjectInitializer& ObjectInitializer);

	/** @brief Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "FlowerPot")
	virtual bool OnInteract() override;

public: 

	/** @brief The capsule  */
	UPROPERTY(VisibleAnywhere, Category = "Tree")
	UCapsuleComponent* TreeCapsuleOverlapCheck;

	/** @brief The tree */
	UPROPERTY(EditAnywhere, Category = "FlowerPot")
	UTree* TreeTrunc;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableEvent_TreeVisible);

	/** @brief The event that is broadcasted when you have to show the tree */
	UPROPERTY(BlueprintAssignable, Category = "Tree")
	FBindableEvent_TreeVisible TreeVisible;

protected:
	/** @brief Make the tree grow */
	void GrowTree();
	/** @brief Plant the seed in the pot */
	void PlantSeed(ASeed * Seed);
	/** @brief Remove the seed from the pot */
	ASeed * RemoveSeed();
	/** Swap seeds */
	ASeed * SwapSeed(ASeed * Seed);

private:
	/** @brief The planted seed */
	ASeed * PlantedSeed;
};
