// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TGCO.h"
#include "TGCOGameMode.h"
#include "TGCOHUD.h"
#include "TGCOCharacter.h"

ATGCOGameMode::ATGCOGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/MyCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATGCOHUD::StaticClass();
}
