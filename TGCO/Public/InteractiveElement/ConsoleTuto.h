// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveElement.h"
#include "ConsoleTuto.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API AConsoleTuto : public AInteractiveElement
{
	GENERATED_UCLASS_BODY()

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Method called when the player wants to use the object which is currently hightlighted.
	//This method will be overriden by each of the class' children
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	virtual bool OnInteract() override;
	
	//Getter / Setter / Is
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
		bool IsUnlocked();

	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
		void SetUnlocked(bool _unlock);

protected:
	bool bIsUnlocked; //whether the console is unlocked
};
