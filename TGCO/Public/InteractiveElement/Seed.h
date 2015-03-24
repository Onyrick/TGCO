
#pragma once

#include "InteractiveElement/InteractiveElement.h"
#include "Seed.generated.h"

/**
 * @brief A seed you can to plant in @ref AFlowerPot
 * 	
 * 	@sa AInteractiveElement
 */
UCLASS()
class TGCO_API ASeed : public AInteractiveElement
{
	GENERATED_BODY()

public:
	/** @brief Constructor */
	ASeed(const FObjectInitializer& ObjectInitializer);

	/** @brief Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "Seed")
	virtual bool OnInteract() override;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableEvent_SeedPicked);

	/** @brief Called when the Element is interacted */
	UPROPERTY(BlueprintAssignable, Category = "Seed")
	FBindableEvent_SeedPicked SeedPicked;

};
