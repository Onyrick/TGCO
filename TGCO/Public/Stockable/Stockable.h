// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Triggerable.h"
#include "Stockable.generated.h"

/**
* TODO
*/
UCLASS()
class TGCO_API AStockable : public ATriggerable
{
	GENERATED_BODY()

public:
	/** Constructors */
	AStockable(const FObjectInitializer& ObjectInitializer);

	/** When the Player enters the area where he can use an object, this interactive element receives OnComponentBeginOverlap. */
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/** When the Player leaves the area where he can use an object, this interactive element receives OnComponentEndOverlap. */
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Getter */
	UFUNCTION(BlueprintCallable, Category = "Stockable")
	virtual FString GetDescription();

	UFUNCTION(BlueprintCallable, Category = "Stockable")
	virtual UTexture2D* GetInventoryImageTexture();
	
	/** The description wirtten in the inventory when the player click on this item*/
	UPROPERTY(EditAnywhere, Category = "Stockable")
	FString sDescription;

	/** The UMG Image shown in the inventory */
	UPROPERTY(EditAnywhere, Category = "Stockable")
	UTexture2D* InventoryImageTexture;
};
