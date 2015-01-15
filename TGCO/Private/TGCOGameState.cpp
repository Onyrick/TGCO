// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOGameState.h"

ATGCOGameState::ATGCOGameState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	iPlayersEnergy		= 0;
	iMaxPlayersEnergy	= 1000;
}

void ATGCOGameState::AddEnergy(int32 iEnergyAmount)
{
	UE_LOG(LogTest, Warning, TEXT("Previous Energy : %f"), iPlayersEnergy);
	iPlayersEnergy = FMath::Min(iMaxPlayersEnergy, iPlayersEnergy + iEnergyAmount);
	UE_LOG(LogTest, Warning, TEXT("Next Energy : %f"), iPlayersEnergy);
}

void ATGCOGameState::DecreaseEnergy(int32 iEnergyAmount)
{
	UE_LOG(LogTest, Warning, TEXT("Previous Energy : %f"), iPlayersEnergy);
	if (iEnergyAmount < 0)
	{
		iEnergyAmount = -iEnergyAmount;
	}

	iPlayersEnergy = FMath::Max(0, iPlayersEnergy - iEnergyAmount);

	UE_LOG(LogTest, Warning, TEXT("Next Energy : %f"), iPlayersEnergy);

	if (!CheckRemainingEnergy())
	{
		//Game Over
		UE_LOG(LogDebug, Warning, TEXT("GameOver"));
	}
}

bool ATGCOGameState::CheckRemainingEnergy()
{
	return iPlayersEnergy > 0;
}