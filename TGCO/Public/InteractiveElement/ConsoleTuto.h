// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveElement.h"
#include "ConsoleTuto.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API AConsoleTuto : public AActor, public IInteractiveElement
{
	GENERATED_UCLASS_BODY()

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Method called when the player wants to use the object which is currently hightlighted.
	//This method will be overriden by each of the class' children
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Console Tuto")
		virtual void OnInteract();
	
	//Getter / Setter / Is
	UFUNCTION(BlueprintCallable, Category = "Console Tuto")
		bool IsUnlocked();

	UFUNCTION(BlueprintCallable, Category = "Console Tuto")
		void SetUnlocked(bool _unlock);

protected:
	bool bIsUnlocked; //whether the console is unlocked
};
