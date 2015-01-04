// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveElement.generated.h"

UCLASS()
class TGCO_API AInteractiveElement : public AActor
{
	GENERATED_BODY()
public:
	//Constructors
	AInteractiveElement(const FObjectInitializer& PCIP);

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
	// This function is called when the player look away from the Element
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
		virtual void OnLookAway();

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Set the element as being interactible
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
		virtual void SetInteractive(bool _interactive);

	//////////////////////////////////////////////////////////////////////////////////////////////
	//for an element to be hightlighted it needs the player to look at it and that the player is close enough
	// to use it.To know if the player is close enough it listens to the evenement OnComponentBeginOverlap
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION()
		virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//////////////////////////////////////////////////////////////////////////////////////////////
	//When the player leaves the area where he can use an object, this interactive element receives
	//	OnComponentEndOverlap so that it can stop the highlighting
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION()
		virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "Triggers")
		UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, Category = "Static Meshes")
		UStaticMeshComponent* StaticMesh;

protected:
	bool bIsInteractive; //whether the element can be interacted with
	bool bCloseEnough; //wether the player is close enough to the element to be able to interact with it
};