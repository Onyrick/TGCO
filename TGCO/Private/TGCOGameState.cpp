// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOGameState.h"
#include "TGCOPlayerState.h"
#include "TGCOGameInstance.h"
#include "Net/UnrealNetwork.h"

ATGCOGameState::ATGCOGameState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	iPlayersEnergy = 500;
	iPlayersEnergyIncrement = 1;
	iMaxPlayersEnergy = 1000;
	fLastRegenTime = 0.f;
	fRegenTime = 0.1f;
	fResumeRegenAfterDecrease = 2.5f;
	MapUnlockSkills.Add(0, "STOP");
	MapUnlockSkills.Add(1, "SLOW");
	MapUnlockSkills.Add(2, "SPEED");
}

const TMap<int, FString>& ATGCOGameState::GetUnlockSkills()
{
	return MapUnlockSkills;
}

void ATGCOGameState::UpdateEnergy()
{
	float gameTime = this->GetWorld()->GetTimeSeconds();
	if (gameTime - fLastRegenTime >= fRegenTime)
	{
		iPlayersEnergy = FMath::Min(iMaxPlayersEnergy, iPlayersEnergy + iPlayersEnergyIncrement);
		fLastRegenTime = gameTime;
	}
	
}

void ATGCOGameState::AddEnergy(int32 iEnergyAmount)
{
	if (Role < ROLE_Authority)
	{
		ServerAddEnergy(iEnergyAmount);
	}
	else
	{
		iPlayersEnergy = FMath::Min(iMaxPlayersEnergy, iPlayersEnergy + iEnergyAmount);
	}
}

bool ATGCOGameState::ServerAddEnergy_Validate(int32 iEnergyAmount)
{
	return true;
}

void ATGCOGameState::ServerAddEnergy_Implementation(int32 iEnergyAmount)
{
	AddEnergy(iEnergyAmount);
}

void ATGCOGameState::IncreaseEnergyMax(int32 iEnergyAmount)
{
	if (Role < ROLE_Authority)
	{
		ServerIncreaseEnergyMax(iEnergyAmount);
	}
	else
	{
		iMaxPlayersEnergy += iEnergyAmount;
	}
}

bool ATGCOGameState::ServerIncreaseEnergyMax_Validate(int32 iEnergyAmount)
{
	return true;
}

void ATGCOGameState::ServerIncreaseEnergyMax_Implementation(int32 iEnergyAmount)
{
	IncreaseEnergyMax(iEnergyAmount);
}

void ATGCOGameState::DecreaseEnergy(int32 iEnergyAmount)
{
	if (Role < ROLE_Authority)
	{
		return ServerDecreaseEnergy(iEnergyAmount);
	}
	else
	{
		if (iEnergyAmount < 0)
		{
			iEnergyAmount = -iEnergyAmount;
		}

		iPlayersEnergy = FMath::Max(0, iPlayersEnergy - iEnergyAmount);

		UE_LOG(LogTest, Warning, TEXT("Next Energy : %d"), iPlayersEnergy);
		fLastRegenTime = this->GetWorld()->GetTimeSeconds() + fResumeRegenAfterDecrease;
	}
}

bool ATGCOGameState::ServerDecreaseEnergy_Validate(int32 iEnergyAmount)
{
	return true;
}

void ATGCOGameState::ServerDecreaseEnergy_Implementation(int32 iEnergyAmount)
{
	DecreaseEnergy(iEnergyAmount);
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

void ATGCOGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(ATGCOGameState, iPlayersEnergy);
}