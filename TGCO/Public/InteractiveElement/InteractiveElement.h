#pragma once

#include "InteractiveElement.generated.h"

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UInteractiveElement :
	public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IInteractiveElement{
	GENERATED_IINTERFACE_BODY()
public:

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Method called when the player wants to use the object which is currently hightlighted.
	//This method will be overriden by each of the class' children
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
		virtual void OnInteract();
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Method used to highlight the interactive element that the player is currently looking at.
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
		virtual void Highlight(bool _highlight);
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Check whether or not the targeted element is currently active(eg the flower pot in the past 
	//	is not interactive until the player grabs the seed)
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
		virtual bool IsInteractive();

	//////////////////////////////////////////////////////////////////////////////////////////////
	//for an element to be hightlighted it needs the player to look at it and that the player is close
	//	enough to use it.To know if the player is looking at the element it listens to the evenement OnLookAt
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
		virtual void OnLookAt();

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Set the element as being interactible
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
		virtual void SetInteractive(bool _interactive);

	//////////////////////////////////////////////////////////////////////////////////////////////
	//for an element to be hightlighted it needs the player to look at it and that the player is close enough
	// to use it.To know if the player is close enough it listens to the evenement OnComponentBeginOverlap
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
		virtual void OnComponentBeginOverlap();
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//When the player leaves the area where he can use an object, this interactive element receives
	//	OnComponentEndOverlap so that it can stop the highlighting
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
		virtual void OnComponentEndOverlap();

protected:
	bool bIsInteractive; //whether the element can be interacted with
};