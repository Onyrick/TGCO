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
	iPlayersEnergy = FMath::Min(iMaxPlayersEnergy, iPlayersEnergy + iEnergyAmount);
}

void ATGCOGameState::DecreaseEnergy(int32 iEnergyAmount)
{

	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, FString::Printf(TEXT("Previous Energy : %f"), iEnergyAmount));
	if (iEnergyAmount < 0)
	{
		iEnergyAmount = -iEnergyAmount;
	}

	iPlayersEnergy = FMath::Max(0, iPlayersEnergy - iEnergyAmount);

	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, FString::Printf(TEXT("Next Energy : %f"), iEnergyAmount));

	if (!CheckRemainingEnergy())
	{
		//Game Over
	}
}

bool ATGCOGameState::CheckRemainingEnergy()
{
	return iPlayersEnergy > 0;
}