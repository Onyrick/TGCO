// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

public:
	/** Add an amount of energy to the total Player's energy */
	UFUNCTION(BlueprintCallable, Category = "Players")
	void AddEnergy(int32 iEnergyAmount);

	/** Remove an amount of energy to the total Player's energy*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	void DecreaseEnergy(int32 iEnergyAmount);

	/** Get the Player's energy*/
	UFUNCTION(BlueprintCallable, Category = "Players")
	int32 GetEnergy();

private:

	/** Check if Players have remaining energy and can continue the game. If not launch Game Over. */
	bool CheckRemainingEnergy();

};

FORCEINLINE int32 ATGCOGameState::GetEnergy(void){ return iPlayersEnergy;  }
