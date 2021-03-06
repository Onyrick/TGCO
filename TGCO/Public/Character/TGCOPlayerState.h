

#pragma once

#include "GameFramework/PlayerState.h"
#include "Stockable.h"
#include "ShootMode.h"
#include "PlayerStatus.h"
#include "TGCOPlayerState.generated.h"

/**
 * @brief	A PlayerState is created for every player on a server (or in a standalone game).
 * 			PlayerStates are replicated to all clients, and contain network game relevant
 * 			information about the player, such as player name, score, etc.
 */
UCLASS()
class TGCO_API ATGCOPlayerState : public APlayerState
{
	GENERATED_BODY()
public:

	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	ATGCOPlayerState(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief	Return PlayerNumber.
	 *
	 * @return	PlayerNumber number of the player.
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	int32 GetPlayerNumber();

	/**
	 * @brief	Sets player number.
	 *
	 * @param	NewPlayerNumber	The new player number.
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void SetPlayerNumber(int32 NewPlayerNumber);

	/**
	 * @brief	Function that set PlayerNumber. 
	 * 			Call on server by client.
	 *
	 * @param	NewPlayerNumber	The new player number.
	 */
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "PlayerState")
	void ServerSetPlayerNumber(int32 NewPlayerNumber);

	/**
	 * @brief	Copies the properties described by PlayerState.
	 *
	 * @param 	PlayerState	If non-null, state of the player.
	 */
	virtual void CopyProperties(APlayerState* PlayerState) override;

	/**
	 * @brief	Adds a new inventory item.
	 *
	 * @param 	_item	If non-null, the item.
	 */
	void AddNewInventoryItem(AStockable* _item);
	/**
	 * @brief	Removes the inventory item described by _item.
	 *
	 * @param 	_item	If non-null, the item.
	 */
	void RemoveInventoryItem(AStockable* _item);

	/**
	 * @brief	Sets Props affected.
	 *
	 * @param 	PropsAffected	If non-null, the properties affected.
	 */
	void SetPropsAffected(AProps* PropsAffected);

	/**
	 * @brief	Query if a Props is affected.
	 *
	 * @return	true if Props is affected, false if not.
	 */
	bool IsPropsAffected();

	/**
	 * @brief	Gets shoot mode used.
	 *
	 * @return	The shoot mode used.
	 */
	EShootMode::Type GetModUsed();

	/**
	 * @brief	Sets shoot mode used.
	 *
	 * @param	_mod	The shoot mode.
	 */
	void SetModUsed(EShootMode::Type _mod);

	/**
	 * @brief	Gets inventory list items.
	 *
	 * @return	null if it fails, else the inventory list items.
	 */
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
	/** @brief   Player number (0 = Maximilien = future / 1 = Samantha = past) */
	UPROPERTY(Replicated)
	int32 PlayerNumber;
	
	/** @brief   Array of stockable element to manage an inventory list */
	TArray<AStockable*> InventoryListItems;

	/** @brief  Pointer to the Props who is affected by time */
	AProps* PropsAffectedByTime;

	/** Mod Used on this Props */
	EShootMode::Type ModUsedOnProps;
};
