// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Props.h"
#include <ctime>

#include "GameFramework/GameState.h"
#include "ShootMode.h"
#include "TGCOGameState.generated.h"

/**
 * State of the game
 * Take care of energy for Players
 * GameState exists on the server and all clients
 */
UCLASS()
class TGCO_API ATGCOGameState : public AGameState
{
	GENERATED_BODY()

public:
	/** Constructors */
	ATGCOGameState(const FObjectInitializer& ObjectInitializer);

	/** Get skills unlock by players */
	const TMap<int, EShootMode::Type>& GetUnlockSkills();

	/** Manage the Players Energy */
	void ManagePlayersEnergy();

	/** Add an amount of energy to the total Player's energy */
	UFUNCTION(BlueprintCallable, Category = "Players")
	void UpdateEnergy();

	/** Add an amount of energy to the total Player's energy */
	UFUNCTION(BlueprintCallable, Category = "Players")
	void AddEnergy(int32 iEnergyAmount);

	/** Remove an amount of energy to the total Player's energy*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	void DecreaseEnergy(int32 iEnergyAmount, bool monsterHit = false);

	/** Increase the maximum amount of Players energy */
	UFUNCTION(BlueprintCallable, Category = "Players")
	void IncreaseEnergyMax(int32 iEnergyAmount);

	/** Get the Player's current energy*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	int32 GetEnergy();

	/** Get the Player's max energy*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	int32 GetMaxEnergy();

	/** Remove all widgets attached to viewport */
	UFUNCTION(Netmulticast, reliable)
	void MulticastRemoveAllWidgets();

	/** TODO */
	UFUNCTION(Netmulticast, reliable)
	void MulticastGoToPlayingState();

	/** Check if Players have remaining energy and can continue the game. If not launch Game Over. */
	bool CheckRemainingEnergy();

private:

	UFUNCTION(Server, WithValidation, reliable)
	void ServerIncreaseEnergyMax(int32 iEnergyAmount);

private:
	/*
	UFUNCTION(NetMulticast)
	void MulticastAddEnergy(int32 iEnergyAmount);
	*/
	/** Array that contains the skill that the Player unlock */
	TMap<int, EShootMode::Type> MapUnlockSkills;

protected:
	/** Amount of energy remaining for both Players */
	UPROPERTY(SaveGame, Replicated)
	int32 iPlayersEnergy;
	int32 iPlayersEnergyIncrement;
	float fLastRegenTime;
	float fRegenTime;
	float fResumeRegenAfterDecrease;

private:
	/** Maximum amount of energy Players can have */
	UPROPERTY(SaveGame, Replicated)
	int32 iMaxPlayersEnergy;

};

FORCEINLINE int32 ATGCOGameState::GetEnergy(void){ return iPlayersEnergy; }
FORCEINLINE int32 ATGCOGameState::GetMaxEnergy(void){ return iMaxPlayersEnergy; }
