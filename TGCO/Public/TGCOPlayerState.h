

#pragma once

#include "GameFramework/PlayerState.h"
#include "Stockable.h"
#include "TGCOPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API ATGCOPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ATGCOPlayerState(const FObjectInitializer& ObjectInitializer);

	/** Return PlayerNumber 
	* @return PlayerNumber number of the player
	*/
	UFUNCTION(BlueprintCallable, Category = "Online")
	int32 GetPlayerNumber();

	/** Set PlayerNumber */
	UFUNCTION(BlueprintCallable, Category = "Online")
	void SetPlayerNumber(int32 NewPlayerNumber);

	/** Set PlayerNumber from server */
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Online")
	void ServerSetPlayerNumber(int32 NewPlayerNumber);

	/** Copy properties which need to be saved in inactive PlayerState */
	virtual void CopyProperties(APlayerState* PlayerState) override;

	/** Add and Remove Item*/
	void AddNewInventoryItem(AStockable* _item);
	void RemoveInventoryItem(AStockable* _item);

protected:
	/** Player number (0 = Maximilien = futur / 1 = Samantha = past */
	UPROPERTY(Replicated)
	int32 PlayerNumber;
	
	TArray<AStockable*> InventoryListItems;
};
