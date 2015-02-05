// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/GameMode.h"
#include "TGCOGameMode.generated.h"

UCLASS(minimalapi)
class ATGCOGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ATGCOGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;

protected:
	/** Return game session class to use */
	virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;

private:
	/** select best spawn point for player */
	virtual AActor* ChoosePlayerStart(AController* Player) override;
};
