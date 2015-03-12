// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveElement.generated.h"

/**
* TODO
*/
UCLASS(Abstract)
class TGCO_API AInteractiveElement : public AActor
{
	GENERATED_BODY()

public:
	/** Constructors */
	AInteractiveElement(const FObjectInitializer& ObjectInitializer);

	/**
	 * Method called when the Player wants to use the object which is currently highlighted.
	 * This method will be overridden by each children classes.
	 */
	virtual bool OnInteract() PURE_VIRTUAL(AInteractiveElement::OnInteract, return false;);
	
	/** Method used to highlight the interactive element that the player is currently looking at. */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	virtual void Highlight(bool _highlight);
	
	/** 
	 * Check whether or not the targeted element is currently active as Interactive
	 */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	virtual bool IsInteractive();

	/**
	 * For an element to be highlighted it needs the Player to look at it and that the Player is close
	 * enough to use it. To know if the Player is looking at the element it listens to the event OnLookAt
	 */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	virtual void OnLookAt();

	/** Set the element as being active as Interactive so the Player can interact with */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	virtual void SetInteractive(bool bInteractive);

	/** When the Player enters the area where he can use an object, this interactive element receives OnComponentBeginOverlap. */
	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/** When the Player leaves the area where he can use an object, this interactive element receives OnComponentEndOverlap. */
	UFUNCTION()
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** TODO */
	UPROPERTY(EditAnywhere, Category = "Triggers")
	UBoxComponent* TriggerBox;

	/** TODO */
	UPROPERTY(EditAnywhere, Category = "Static Meshes")
	UStaticMeshComponent* StaticMesh;
	
	/** TODO */
	UPROPERTY(EditAnywhere, Category = "InteractiveElementComponents")
	bool IsLookedAt;

	/** TODO */
	UPROPERTY(EditAnywhere, Category = "InteractiveElementComponents")
	bool bCanExistsPastFuture;

	/** TODO */
	UPROPERTY(EditAnywhere, Category = "InteractiveElementComponents", meta = (EditCondition = "bCanExistsPastFuture"))
	AActor* FutureElement;

protected:

	/** Whether the element can be interacted with */
	bool bIsInteractive;
	/** Whether the Player is close enough to the element to be able to interact with it */
	bool bCloseEnough;
};
