
#pragma once

#include "GameFramework/Actor.h"
#include "Triggerable.h"
#include "Stockable.generated.h"

/**
* @class AStockable
* 
* @brief Stockable interface. Class inherited from Astockable can be store in the player's inventory.
* 		 It is composed by a description and a image texture to display in inventory.
*/
UCLASS()
class TGCO_API AStockable : public ATriggerable
{
	GENERATED_BODY()

public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	AStockable(const FObjectInitializer& ObjectInitializer);

	/** @brief When the Player enters the area where he can use an object, this interactive element receives OnComponentBeginOverlap. */
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/**   
	* @brief Get the description
	* 
	* @return FString The description		 
	*/
	UFUNCTION(BlueprintCallable, Category = "Stockable")
	virtual FString GetDescription();

	/**
	* @brief Get the image texture
	*
	* @return UTexture2D* The image texture
	*/
	UFUNCTION(BlueprintCallable, Category = "Stockable")
	virtual UTexture2D* GetInventoryImageTexture();
	
public:
	/** The description wirtten in the inventory when the player click on this item*/
	UPROPERTY(EditAnywhere, Category = "Stockable")
	FString sDescription;

	/** The UMG Image shown in the inventory */
	UPROPERTY(EditAnywhere, Category = "Stockable")
	UTexture2D* InventoryImageTexture;
};
