// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOGameState.h"
#include "TGCOPlayerState.h"

ATGCOGameState::ATGCOGameState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	iPlayersEnergy = 0;
	iMaxPlayersEnergy = 1000;
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

void ATGCOGameState::ExchangeCharacter(){

	UE_LOG(LogTest, Warning, TEXT("Exchange characters"));
	TArray<APlayerState*> MyPlayerArray = GetWorld()->GetGameState()->PlayerArray;
	if (MyPlayerArray.Num() == 2){

		UE_LOG(LogTest, Warning, TEXT("Is server : %s"), (GetWorld()->IsServer()) ? "true" : "false");

		ATGCOPlayerState* Server = Cast<ATGCOPlayerState>(MyPlayerArray[0]);
		ATGCOPlayerState* Client = Cast<ATGCOPlayerState>(MyPlayerArray[1]);

		int32 serverNb = Server->GetPlayerNumber();
		int32 clientNb = Server->GetPlayerNumber();
		
		UE_LOG(LogTest, Warning, TEXT("Server : %i"), serverNb);
		UE_LOG(LogTest, Warning, TEXT("Client : %i"), clientNb);

		if (GetWorld()->IsServer())
		{
			UE_LOG(LogTest, Warning, TEXT("I am the server"));

			UE_LOG(LogTest, Warning, TEXT("Server : %i"), serverNb);
			UE_LOG(LogTest, Warning, TEXT("Client : %i"), clientNb);

			Server->SetPlayerNumber(clientNb);
			Client->SetPlayerNumber(serverNb);

			UE_LOG(LogTest, Warning, TEXT("Server : %i"), serverNb);
			UE_LOG(LogTest, Warning, TEXT("Client : %i"), clientNb);
		}
		else
		{
			UE_LOG(LogTest, Warning, TEXT("I am the client"));

			UE_LOG(LogTest, Warning, TEXT("Server : %i"), serverNb);
			UE_LOG(LogTest, Warning, TEXT("Client : %i"), clientNb);

			Server->ServerSetPlayerNumber(clientNb);
			Client->ServerSetPlayerNumber(serverNb);

			UE_LOG(LogTest, Warning, TEXT("Server : %i"), serverNb);
			UE_LOG(LogTest, Warning, TEXT("Client : %i"), clientNb);
		}

		OnExchangeCharacters.Broadcast();
	}
}