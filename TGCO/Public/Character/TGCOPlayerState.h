

#pragma once

#include "GameFramework/PlayerState.h"
#include "Stockable.h"
#include "ShootMode.h"
#include "PlayerStatus.h"
#include "TGCOPlayerState.generated.h"

/**
 * A PlayerState is created for every player on a server (or in a standalone game). 
 * PlayerStates are replicated to all clients, and contain network game relevant information about the player, such as playername, score, etc.
 */
UCLASS()
class TGCO_API ATGCOPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	/** Constructors */
	ATGCOPlayerState(const FObjectInitializer& ObjectInitializer);

	/** 
	 * Return PlayerNumber 
	 *
	 * @return PlayerNumber number of the player
	 */
	UFUNCTION(BlueprintCallable, Category = "Online")
	int32 GetPlayerNumber();

	/** Set PlayerNumber */
	UFUNCTION(BlueprintCallable, Category = "Online")
	void SetPlayerNumber(int32 NewPlayerNumber);

	/** Set PlayerNumber from client on server */
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Online")
	void ServerSetPlayerNumber(int32 NewPlayerNumber);

	/** Copy properties which need to be saved in inactive PlayerState */
	virtual void CopyProperties(APlayerState* PlayerState) override;

	/** Add and Remove Item to inventory */
	void AddNewInventoryItem(AStockable* _item);
	void RemoveInventoryItem(AStockable* _item);

	/** Set the Props affected by time */
	void SetPropsAffected(AProps* PropsAffected);

	/** Test whether a Props is affected */
	bool IsPropsAffected();

	/** Get the mod used on the Props */
	EShootMode::Type GetModUsed();

	/** Set the mod used on the Props */
	void SetModUsed(EShootMode::Type _mod);

	/** Get items in Player inventory list */
	UFUNCTION(BlueprintCallable, Category = "TGCOPlayerState")
	TArray<AStockable*> GetInventoryListItems();

	/**   
	* @brief Switch game between game and puzzle    
	*
	* @param NewViewTarget New target for camera
	*/
	void SwitchGamePuzzle(AActor* NewViewTarget);

	/** @brief Current state of the player */
	EPlayerStatus::State eCurrentState;

protected:
	/** Player number (0 = Maximilien = future / 1 = Samantha = past */
	UPROPERTY(Replicated)
	int32 PlayerNumber;
	
	/** Array of stockable element to manage an inventory list */
	TArray<AStockable*> InventoryListItems;

	/** Pointer to the Props who is affected by time */
	AProps* PropsAffectedByTime;

	/** Mod Used on this prop */
	EShootMode::Type ModUsedOnProp;

	/** To know if the player is in a puzzle (can't shoot / open the inventory / change mode...)*/
	bool bIsInPuzzle;
};
