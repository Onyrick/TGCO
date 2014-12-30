// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "TGCOGameSession.h"
#include "TGCOGameInstance.generated.h"

namespace TGCOGameInstanceState
{
	extern const FName None;
	extern const FName WelcomeScreen;
	extern const FName MainMenu;
	extern const FName Playing;
}

/**
 * 
 */
UCLASS(config = Game)
class TGCO_API UTGCOGameInstance : public UGameInstance
{
	GENERATED_UCLASS_BODY()

private: 
	FName CurrentState;
	FName PendingState;

	/** Delegate for callbacks to Tick */
	FTickerDelegate TickDelegate;

public:
	bool Tick(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Online")
	class ATGCOGameSession* GetGameSession() const;

	virtual void Init() override;
	virtual void StartGameInstance() override;

	/** Sends the game to the specified state. */
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void GotoState(FName NewState);

	/** Obtains the initial welcome state, which can be different based on platform */
	UFUNCTION(BlueprintCallable, Category = "GameState")
	FName GetInitialState();

	/** Sends the game to the initial startup/frontend state  */
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void GotoInitialState();

private:
	void MaybeChangeState();
	void EndCurrentState(FName NextState);
	void BeginNewState(FName NewState, FName PrevState);

	void BeginWelcomeScreenState();
	void BeginMainMenuState();
	void BeginPlayingState();

	void EndWelcomeScreenState();
	void EndMainMenuState();
	void EndPlayingState();
	
};
