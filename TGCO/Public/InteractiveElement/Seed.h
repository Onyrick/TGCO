

#pragma once

#include "InteractiveElement/InteractiveElement.h"
#include "Seed.generated.h"

/**
 *
 */
UCLASS()
class TGCO_API ASeed : public AInteractiveElement
{
	GENERATED_BODY()


		//Constructors
		ASeed(const FObjectInitializer& PCIP);
public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Method called when the player wants to use the object
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Seed")
	virtual bool OnInteract() override;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FBindableEvent_SeedPicked
		);

	/** Called when Server Search is finished */
	UPROPERTY(BlueprintAssignable, Category = "Seed")
		FBindableEvent_SeedPicked SeedPicked;

};
