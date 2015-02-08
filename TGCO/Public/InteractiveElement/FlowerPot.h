// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractiveElement/InteractiveElement.h"
#include "Props/Tree.h"
#include "InteractiveElement/Seed.h"
#include "FlowerPot.generated.h"

/**
 * TODO
 */
UCLASS()
class TGCO_API AFlowerPot : public AInteractiveElement
{
	GENERATED_BODY()

public:
	/** Constructors */
	AFlowerPot(const FObjectInitializer& PCIP);

	/** Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "FlowerPot")
	virtual bool OnInteract() override;
	
	/** TODO */
	UPROPERTY(VisibleAnywhere, Category = "Tree")
	UCapsuleComponent* TreeCapsuleOverlapCheck;

	/** TODO */
	UPROPERTY(EditAnywhere, Category = "FlowerPot")
	UTree* TreeTrunc;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableEvent_TreeVisible);

	/** Called when TODO */
	UPROPERTY(BlueprintAssignable, Category = "Tree")
	FBindableEvent_TreeVisible TreeVisible;

protected:
	/** TODO */
	void GrowTree();
	/** TODO */
	void PlantSeed(ASeed * Seed);
	/** TODO */
	ASeed * RemoveSeed();
	/** TODO */
	ASeed * SwapSeed(ASeed * Seed);

private:
	/** TODO */
	ASeed * PlantedSeed;
};
