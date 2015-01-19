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
	UE_LOG(LogTest, Warning, TEXT("Previous Energy : %d"), iPlayersEnergy);
	iPlayersEnergy = FMath::Min(iMaxPlayersEnergy, iPlayersEnergy + iEnergyAmount);
	UE_LOG(LogTest, Warning, TEXT("Next Energy : %d"), iPlayersEnergy);
}

bool ATGCOGameState::DecreaseEnergy(int32 iEnergyAmount)
{
	UE_LOG(LogTest, Warning, TEXT("Previous Energy : %d"), iPlayersEnergy);
	if (iEnergyAmount < 0)
	{
		iEnergyAmount = -iEnergyAmount;
	}

	iPlayersEnergy = FMath::Max(0, iPlayersEnergy - iEnergyAmount);

	UE_LOG(LogTest, Warning, TEXT("Next Energy : %d"), iPlayersEnergy);

	return CheckRemainingEnergy();
}

bool ATGCOGameState::CheckRemainingEnergy()
{
	return iPlayersEnergy > 0;
}