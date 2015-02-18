// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Props.h"
#include <ctime>

#include "GameFramework/GameState.h"
#include "TGCOGameState.generated.h"

/**
 * TODO
 */
UCLASS()
class TGCO_API ATGCOGameState : public AGameState
{
	GENERATED_UCLASS_BODY()

protected:
	/** Amount of energy remaining for both Players */
	UPROPERTY(SaveGame)
	int32 iPlayersEnergy;

private:
	/** Maximum amount of energy Players can have */
	int32 iMaxPlayersEnergy;

	/** Seed to generate random puzzle */
	int32 iSeed;

public:

	/** Get skills unlock by players */
	const TMap<int, FString>& GetUnlockSkills();

	/** Add an amount of energy to the total Player's energy */
	UFUNCTION(BlueprintCallable, Category = "Players")
	void AddEnergy(int32 iEnergyAmount);

	/** Remove an amount of energy to the total Player's energy*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	bool DecreaseEnergy(int32 iEnergyAmount);

	/** Get the Player's energy*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	int32 GetEnergy();

	/** Get the seed */
	UFUNCTION(BlueprintCallable, Category = "Players")
	int32 GetSeed();

	/** Set a random seed */
	UFUNCTION(BlueprintCallable, Category = "Players")
	void SetRandomSeed();

	/** Remove all widgets attached to viewport */
	UFUNCTION(Netmulticast, reliable)
	void MulticastRemoveAllWidgets();

	UFUNCTION(Netmulticast, reliable)
	void MulticastGoToPlayingState();

private:

	/** Check if Players have remaining energy and can continue the game. If not launch Game Over. */
	bool CheckRemainingEnergy();

	/** Array that contains the skill that the Player unlock */
	TMap<int, FString> MapUnlockSkills;

};

FORCEINLINE int32 ATGCOGameState::GetEnergy(void){ return iPlayersEnergy;  }
