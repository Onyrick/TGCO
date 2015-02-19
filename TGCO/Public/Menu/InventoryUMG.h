// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Stockable.h"
#include "UMG.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUMG.generated.h"

/**
* TODO
*/
UCLASS()
class TGCO_API UInventoryUMG : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Constructors */
	UInventoryUMG(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InventoryUMG")
	void AddNewItem(AStockable* _stockable);
};
