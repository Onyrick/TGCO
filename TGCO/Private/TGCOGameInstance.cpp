// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOGameInstance.h"

#include "Engine.h"

namespace TGCOGameInstanceState
{
	const FName None = FName(TEXT("None"));
	const FName WelcomeScreen = FName(TEXT("WelcomeScreen"));
	const FName MainMenu = FName(TEXT("MainMenu"));
	const FName Playing = FName(TEXT("Playing"));
}

UTGCOGameInstance::UTGCOGameInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	CurrentState = TGCOGameInstanceState::None;
}


void UTGCOGameInstance::Init()
{
	Super::Init();
	
	// Register delegate for ticker callback
	TickDelegate = FTickerDelegate::CreateUObject(this, &UTGCOGameInstance::Tick);
	FTicker::GetCoreTicker().AddTicker(TickDelegate);
}

void UTGCOGameInstance::Shutdown()
{
	Super::Shutdown();

	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(TickDelegate);
}


void UTGCOGameInstance::StartGameInstance()
{
	Super::StartGameInstance();

	GotoInitialState();
}

// starts a host session
bool UTGCOGameInstance::HostGame(ULocalPlayer* LocalPlayer, const FString& MapName)
{
	ATGCOGameSession* const GameSession = GetGameSession();
	if (GameSession)
	{
		// add callback delegate for completion
	//	GameSession->OnCreatePresenceSessionComplete().AddUObject(this, &UTGCOGameInstance::OnCreatePresenceSessionComplete);

		bool const bIsLanMatch = true;

		if (GameSession->HostSession(LocalPlayer->GetPreferredUniqueNetId(), "TGCOSession", MapName, bIsLanMatch, true, ATGCOGameSession::DEFAULT_NUM_PLAYERS))
		{
			// If any error occured in the above, pending state would be set
			if ((PendingState == CurrentState) || (PendingState == TGCOGameInstanceState::None))
			{
				// Go ahead and go into loading state now
				// If we fail, the delegate will handle showing the proper messaging and move to the correct state
				
				// ShowLoadingScreen();
				// GotoState(TGCOGameInstanceState::Playing);
				return true;
			}
		}
	}

	return false;
}

bool UTGCOGameInstance::Tick(float DeltaSeconds)
{
	MaybeChangeState();

	return true;
}

FName UTGCOGameInstance::GetInitialState()
{
	// Go directly to the main menu
	return TGCOGameInstanceState::MainMenu;
}

void UTGCOGameInstance::GotoInitialState()
{
	GotoState(GetInitialState());
}

void UTGCOGameInstance::GotoState(FName NewState)
{
//	UE_LOG(LogOnline, Log, TEXT("GotoState: NewState: %s"), *NewState.ToString());

	PendingState = NewState;
}

void UTGCOGameInstance::MaybeChangeState()
{
	if ((PendingState != CurrentState) && (PendingState != TGCOGameInstanceState::None))
	{
		FName const OldState = CurrentState;

		// end current state
		EndCurrentState(PendingState);

		// begin new state
		BeginNewState(PendingState, OldState);

		// clear pending change
		PendingState = TGCOGameInstanceState::None;
	}
}

void UTGCOGameInstance::EndCurrentState(FName NextState)
{
	// per-state custom ending code here
	if (CurrentState == TGCOGameInstanceState::WelcomeScreen)
	{
		//EndWelcomeScreenState();
	}
	else if (CurrentState == TGCOGameInstanceState::MainMenu)
	{
		EndMainMenuState();
	}
	else if (CurrentState == TGCOGameInstanceState::Playing)
	{
		//EndPlayingState();
	}

	CurrentState = TGCOGameInstanceState::None;
}

void UTGCOGameInstance::BeginNewState(FName NewState, FName PrevState)
{
	// per-state custom starting code here

	if (NewState == TGCOGameInstanceState::WelcomeScreen)
	{
		//BeginWelcomeScreenState();
	}
	else if (NewState == TGCOGameInstanceState::MainMenu)
	{
		BeginMainMenuState();
	}
	else if (NewState == TGCOGameInstanceState::Playing)
	{
		BeginPlayingState();
	}

	CurrentState = NewState;
}

void UTGCOGameInstance::BeginMainMenuState()
{
	GetWorld()->ServerTravel(FString("/Game/Maps/MainMenuMap"));
}

void UTGCOGameInstance::EndMainMenuState()
{

}

void UTGCOGameInstance::BeginPlayingState()
{
	GetWorld()->ServerTravel(FString("/Game/Maps/Room1"));
}

class ATGCOGameSession* UTGCOGameInstance::GetGameSession() const
{
	UWorld* const World = GetWorld();
	if (World)
	{
		AGameMode* const Game = World->GetAuthGameMode();
		if (Game)
		{
			return Cast<ATGCOGameSession>(Game->GameSession);
		}
	}

	return nullptr;
}

