// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TGCO.h"
#include "TGCOGameMode.h"
#include "TGCOPlayerState.h"
#include "TGCOPlayerController.h"
#include "TGCOGameState.h"
#include "TGCOCharacter.h"
#include "TGCOGameSession.h"
#include "TGCOPlayerState.h"
#include "TGCOHUD.h"
#include "Engine.h"

ATGCOGameMode::ATGCOGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = ATGCOHUD::StaticClass();
	GameStateClass = ATGCOGameState::StaticClass();
	PlayerStateClass = ATGCOPlayerState::StaticClass();
	PlayerControllerClass = ATGCOPlayerController::StaticClass();

	bUseSeamlessTravel = false;
}

void ATGCOGameMode::StartPlay()
{
	Super::StartPlay();
}

TSubclassOf<AGameSession> ATGCOGameMode::GetGameSessionClass() const
{
	return ATGCOGameSession::StaticClass();
}

AActor* ATGCOGameMode::ChoosePlayerStart(AController* Player)
{
	APlayerStart* BestStart = NULL;
	for (int32 i = 0; i < PlayerStarts.Num(); i++)
	{
		APlayerStart* TestSpawn = PlayerStarts[i];
		UE_LOG(LogOnline, Log, TEXT("Player start name : %s"), *TestSpawn->GetName());
		if (TestSpawn != NULL)
		{
			if (TestSpawn->GetName().Equals("PlayerStartPast"))
			{
				ATGCOPlayerState* PlayerState = Cast<ATGCOPlayerState>(Player->PlayerState);
				if (PlayerState)
				{
					int32 PlayerNumber = PlayerState->GetPlayerNumber();
					if (PlayerNumber == 1)
					{
						// 1 == Sam == past
						BestStart = TestSpawn;
					}
				}
			}
			else
			{
				if (TestSpawn->GetName().Equals("PlayerStartFutur"))
				{
					ATGCOPlayerState* PlayerState = Cast<ATGCOPlayerState>(Player->PlayerState);
					if (PlayerState)
					{
						int32 PlayerNumber = PlayerState->GetPlayerNumber();
						if (PlayerNumber == 0)
						{
							// 1 == Sam == past
							BestStart = TestSpawn;
						}
					}
				}
				else
				{
					BestStart = TestSpawn;
				}
			}
			
		}
	}

	return BestStart ? BestStart : Super::ChoosePlayerStart(Player);
}
