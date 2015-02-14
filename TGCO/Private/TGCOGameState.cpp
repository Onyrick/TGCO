// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOGameState.h"
#include "TGCOPlayerState.h"
#include "TGCOGameInstance.h"

ATGCOGameState::ATGCOGameState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	iPlayersEnergy = 0;
	iMaxPlayersEnergy = 1000;
	MapUnlockSkills.Add(0, "STOP");
	MapUnlockSkills.Add(1, "SLOW");
	MapUnlockSkills.Add(2, "SPEED");
}

const TMap<int, FString>& ATGCOGameState::GetUnlockSkills()
{
	return MapUnlockSkills;
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

void ATGCOGameState::MulticastRemoveAllWidgets_Implementation()
{
	UGameViewportClient* GVC = GEngine->GameViewport;
	GVC->RemoveAllViewportWidgets();
}
void ATGCOGameState::MulticastGoToPlayingState_Implementation()
{
	UWorld* const World = GetWorld();
	if (World)
	{
		UTGCOGameInstance* GameInstance = Cast<UTGCOGameInstance>(World->GetGameInstance());
		if (GameInstance)
		{
			GameInstance->SetCurrentState(FName(TEXT("Playing")));
		}
	}
}
