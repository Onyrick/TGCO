// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Props.h"
#include <ctime>

#include "GameFramework/GameState.h"
#include "ShootMode.h"
#include "TGCOGameState.generated.h"

/**
 * @brief	State of the game Take care of energy for Players GameState exists on the server and
 * 			all clients.
 */
UCLASS()
class TGCO_API ATGCOGameState : public AGameState
{
	GENERATED_BODY()

public:

	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	ATGCOGameState(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief	Gets unlock skills by players.
	 *
	 * @return	The unlock skills.
	 */
	const TMap<int, EShootMode::Type>& GetUnlockSkills();

	/** @brief	Manage players energy. */
	void ManagePlayersEnergy();

	/** @brief	Updates the Player's energy. */
	UFUNCTION(BlueprintCallable, Category = "Players")
	void UpdateEnergy();

	/**
	* @brief	Add an amount of energy to the total Player's energy.
	*
	* @param	iEnergyAmount	The energy amount.
	*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	void AddEnergy(int32 iEnergyAmount);

	/**
	* @brief	Remove an amount of energy to the total Player's energy.
	*
	* @param	iEnergyAmount	The energy amount.
	* @param	monsterHit   	true if player can die.
	*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	void DecreaseEnergy(int32 iEnergyAmount, bool bCanPlayerDie = false);
	
	/**
	* @brief	Increase the maximum energy players can have by iEnergyAmount.
	*
	* @param	iEnergyAmount	The energy amount.
	*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	void IncreaseEnergyMax(int32 iEnergyAmount);

	/**
	* @brief	Gets the energy.
	*
	* @return	The energy.
	*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	int32 GetEnergy();

	/**
	* @brief	Gets maximum energy.
	*
	* @return	The maximum energy.
	*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	int32 GetMaxEnergy();

	/** @brief	Multicast remove all widgets attached to viewport */
	UFUNCTION(Netmulticast, reliable)
	void MulticastRemoveAllWidgets();

	/** @brief	Multicast go to playing state. */
	UFUNCTION(Netmulticast, reliable)
	void MulticastGoToPlayingState();

	/**
	 * @brief	Determines if Players have remaining energy and can continue the game.
	 *
	 * @return	true if there is still energy, false otherwise.
	 */
	bool CheckRemainingEnergy();

private:
	/**
	* @brief	Increase the maximum energy.
	* 			Called by client on server.
	*
	* @param	iEnergyAmount	The energy amount.
	*/
	UFUNCTION(Server, WithValidation, reliable)
	void ServerIncreaseEnergyMax(int32 iEnergyAmount);

private:

	/** @brief	Array that contains the skill that the Player unlock. */
	TMap<int, EShootMode::Type> MapUnlockSkills;

protected:
	/** @brief   Amount of energy remaining for both Players */
	UPROPERTY(SaveGame, Replicated)
	int32 iPlayersEnergy;
	/** @brief	The players energy increment in time. */
	int32 iPlayersEnergyIncrement;
	/** @brief	The last regen time. */
	float fLastRegenTime;
	/** @brief	The regen time. */
	float fRegenTime;
	/** @brief	The resume regen after decrease. */
	float fResumeRegenAfterDecrease;

private:
	/** @brief  Maximum amount of energy Players can have */
	UPROPERTY(SaveGame, Replicated)
	int32 iMaxPlayersEnergy;

};

/**
 * @brief	Gets the energy.
 *
 * @return	The energy.
 */
FORCEINLINE int32 ATGCOGameState::GetEnergy(void){ return iPlayersEnergy; }

/**
 * @brief	Gets maximum energy.
 *
 * @return	The maximum energy.
 */
FORCEINLINE int32 ATGCOGameState::GetMaxEnergy(void){ return iMaxPlayersEnergy; }
