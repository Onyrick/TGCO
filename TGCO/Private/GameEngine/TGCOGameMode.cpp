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
	if (PlayerPawnBPClass.Class != nullptr)
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
	APlayerStart* BestStart = nullptr;
	for (int32 i = 0; i < PlayerStarts.Num(); i++)
	{
		APlayerStart* TestSpawn = PlayerStarts[i];
		UE_LOG(LogOnline, Log, TEXT("Player start name : %s"), *TestSpawn->GetName());
		if (TestSpawn != nullptr)
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

void ATGCOGameMode::KillPlayersThenRespawn()
{
	UE_LOG(LogDebug, Warning, TEXT("Kill Players and respawn"));

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		ATGCOGameState* GameState = Cast<ATGCOGameState>(World->GetGameState());
		if (GameState != nullptr)
		{	
			for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
			{
				// Get the Controller
				APlayerController * PC = Iterator->Get();
				// Get the pawn attach to this controller
				ATGCOCharacter* Character = Cast<ATGCOCharacter>(PC->GetCharacter());
				// Detach the pawn from the Controller
				// Character->DetachFromControllerPendingDestroy();
				// Spawn a new pawn and get it
				ATGCOCharacter* NewCharacter = Character->SpawnPlayer();
				// Attach it to the Controller
				PC->Possess(NewCharacter);
				// Destroy the old pawn
				Character->Destroy(true, false);
			}
			// Add base energy because die
			GameState->AddEnergy(500);
		}
	}

}

bool ATGCOGameMode::ServerKillPlayersThenRespawn_Validate()
{
	return true;
}

void ATGCOGameMode::ServerKillPlayersThenRespawn_Implementation()
{
	KillPlayersThenRespawn();
}
