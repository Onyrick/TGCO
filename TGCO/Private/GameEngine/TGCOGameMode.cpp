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
	// Set default pawn class to our Blueprinted character
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
				UE_LOG(LogDebug, Warning, TEXT("Forloop PC !"));
				APlayerController * PC = Iterator->Get();
				RestartPlayer(PC);
				/*
				// Get the pawn attach to this controller
				ATGCOCharacter* Character = Cast<ATGCOCharacter>(PC->GetCharacter());
				// Detach the pawn from the Controller
				Character->DetachFromControllerPendingDestroy();
				// Spawn a new pawn and get it
				ATGCOCharacter* NewCharacter = Character->SpawnPlayer();
				// Attach it to the Controller
				PC->Possess(NewCharacter);
				// Destroy the old pawn
				Character->Destroy(true, false);
				*/
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


AActor* ATGCOGameMode::FindPlayerStart(AController* Player, const FString& IncomingName)
{
	ATGCOCharacter* Character = Cast<ATGCOCharacter>(Player->GetPawn());
	if (Character != nullptr)
	{
		AActor* BestStart = nullptr;
		BestStart = PlayerStarts[0];

		FVector CharacterPosition = Character->GetPawnViewLocation();
		FVector BestVector = CharacterPosition - BestStart->GetActorLocation();
		float BestLength = BestVector.Size();

		for (int32 i = 1; i < PlayerStarts.Num(); i++)
		{
			APlayerStart* TestSpawn = PlayerStarts[i];
			UE_LOG(LogOnline, Log, TEXT("Player start name : %s"), *TestSpawn->GetName());
			if (TestSpawn != nullptr)
			{
				FVector TempVector = CharacterPosition - TestSpawn->GetActorLocation();
				float TempLength = TempVector.Size();
				if (TempLength < BestLength)
				{
					BestLength = TempLength;
					BestStart = TestSpawn;
				}
			}
		}

		UE_LOG(LogDebug, Log, TEXT("Player start choose : %s "), *BestStart->GetName());
		return BestStart;
	}

	return Super::FindPlayerStart(Player, IncomingName);
}

void ATGCOGameMode::RestartPlayer(AController* NewPlayer)
{
	UE_LOG(LogDebug, Warning, TEXT("Begin of restart player"));
	if (NewPlayer == NULL || NewPlayer->IsPendingKillPending())
	{
		return;
	}

	UE_LOG(LogTest, Verbose, TEXT("RestartPlayer %s"), (NewPlayer && NewPlayer->PlayerState) ? *NewPlayer->PlayerState->PlayerName : TEXT("Unknown"));

	if (NewPlayer->PlayerState && NewPlayer->PlayerState->bOnlySpectator)
	{
		UE_LOG(LogTest, Verbose, TEXT("RestartPlayer tried to restart a spectator-only player!"));
		return;
	}

	AActor* StartSpot = FindPlayerStart(NewPlayer);

	// if a start spot wasn't found,
	if (StartSpot == NULL)
	{
		UE_LOG(LogDebug, Warning, TEXT("StartSpot is null after FindPlayerStart"));
		// check for a previously assigned spot
		if (NewPlayer->StartSpot != NULL)
		{
			StartSpot = NewPlayer->StartSpot.Get();
			UE_LOG(LogTest, Warning, TEXT("Player start not found, using last start spot"));
		}
		else
		{
			// otherwise abort
			UE_LOG(LogTest, Warning, TEXT("Player start not found, failed to restart player"));
			return;
		}
	}
	// try to create a pawn to use of the default class for this player
	if (NewPlayer->GetPawn() == NULL && GetDefaultPawnClassForController(NewPlayer) != NULL)
	{
		NewPlayer->SetPawn(SpawnDefaultPawnFor(NewPlayer, StartSpot));
	}

	if (NewPlayer->GetPawn() == NULL)
	{
		NewPlayer->FailedToSpawnPawn();
	}
	else
	{
		// initialize and start it up
		InitStartSpot(StartSpot, NewPlayer);

		NewPlayer->Possess(NewPlayer->GetPawn());

		// If the Pawn is destroyed as part of possession we have to abort
		if (NewPlayer->GetPawn() == nullptr)
		{
			NewPlayer->FailedToSpawnPawn();
		}
		else
		{
			// set initial control rotation to player start's rotation
			NewPlayer->ClientSetRotation(NewPlayer->GetPawn()->GetActorRotation(), true);

			FRotator NewControllerRot = StartSpot->GetActorRotation();
			NewControllerRot.Roll = 0.f;
			NewPlayer->SetControlRotation(NewControllerRot);

			SetPlayerDefaults(NewPlayer->GetPawn());
		}
	}

#if !UE_WITH_PHYSICS
	if (NewPlayer->GetPawn() != NULL)
	{
		UCharacterMovementComponent* CharacterMovement = Cast<UCharacterMovementComponent>(NewPlayer->GetPawn()->GetMovementComponent());
		if (CharacterMovement)
		{
			CharacterMovement->bCheatFlying = true;
			CharacterMovement->SetMovementMode(MOVE_Flying);
		}
	}
#endif	//!UE_WITH_PHYSICS
}
