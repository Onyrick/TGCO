
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
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	UInventoryUMG(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InventoryUMG")
	void AddNewItem(AStockable* _stockable);
};
