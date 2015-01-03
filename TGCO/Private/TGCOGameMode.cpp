// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TGCO.h"
#include "TGCOGameMode.h"
#include "TGCOGameState.h"
#include "TGCOCharacter.h"
#include "TGCOGameSession.h"
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
}

void ATGCOGameMode::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, TEXT("Begin Play"));
	}
}

TSubclassOf<AGameSession> ATGCOGameMode::GetGameSessionClass() const
{
	return ATGCOGameSession::StaticClass();
}
