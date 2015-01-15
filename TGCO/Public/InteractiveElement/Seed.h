// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractiveElement/InteractiveElement.h"
#include "Seed.generated.h"

/**
 * TODO
 */
UCLASS()
class TGCO_API ASeed : public AInteractiveElement
{
	GENERATED_BODY()

public:
	/** Constructors */
	ASeed(const FObjectInitializer& PCIP);

	/** Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "Seed")
	virtual bool OnInteract() override;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableEvent_SeedPicked);

	/** Called when the Element is interacted */
	UPROPERTY(BlueprintAssignable, Category = "Seed")
	FBindableEvent_SeedPicked SeedPicked;

};
