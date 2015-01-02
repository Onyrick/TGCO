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
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement Console", meta = (FriendlyName = "On Interact"))
		virtual void OnInteract();

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Method used to highlight the interactive element that the player is currently looking at.
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement Console", meta = (FriendlyName = "Highlight"))
		virtual void Highlight(bool _highlight);

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Check whether or not the targeted element is currently active(eg the flower pot in the past 
	//	is not interactive until the player grabs the seed)
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement  Console", meta = (FriendlyName = "IsInteractive"))
		virtual bool IsInteractive();

	//////////////////////////////////////////////////////////////////////////////////////////////
	//for an element to be hightlighted it needs the player to look at it and that the player is close
	//	enough to use it.To know if the player is looking at the element it listens to the evenement OnLookAt
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement  Console", meta = (FriendlyName = "OnLookAt"))
		virtual void OnLookAt();

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Set the element as being interactible
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement Console", meta = (FriendlyName = "SetInteractive"))
		virtual void SetInteractive(bool _interactive);

	//////////////////////////////////////////////////////////////////////////////////////////////
	//for an element to be hightlighted it needs the player to look at it and that the player is close enough
	// to use it.To know if the player is close enough it listens to the evenement OnComponentBeginOverlap
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement Console", meta = (FriendlyName = "OnComponentBeginOverlap"))
		virtual void OnComponentBeginOverlap();

	//////////////////////////////////////////////////////////////////////////////////////////////
	//When the player leaves the area where he can use an object, this interactive element receives
	//	OnComponentEndOverlap so that it can stop the highlighting
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement Console", meta = (FriendlyName = "OnComponentEndOverlap"))
		virtual void OnComponentEndOverlap();
	
	//Getter / Setter / Is
		bool IsUnlocked();
		void SetUnlocked(bool _unlock);

protected:
	bool bIsUnlocked; //whether the console is unlocked
};
