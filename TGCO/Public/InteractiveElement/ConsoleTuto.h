// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveElement.h"
#include "ConsoleTuto.generated.h"

/**
 * TODO
 */
UCLASS()
class TGCO_API AConsoleTuto : public AInteractiveElement
{
	GENERATED_UCLASS_BODY()

public:
	/** Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	virtual bool OnInteract() override;
	
	/** Getter for bIsUnlocked */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	bool IsUnlocked();

	/** Setter for bIsUnlocked */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	void SetUnlocked(bool _unlock);

protected:
	/** Whether the console is unlocked */
	bool bIsUnlocked;
};
