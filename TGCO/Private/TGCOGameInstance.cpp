// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOGameInstance.h"

#include "Online.h"
#include "Engine.h"

namespace TGCOGameInstanceState
{
	const FName None = FName(TEXT("None"));
	const FName WelcomeScreen = FName(TEXT("WelcomeScreen"));
	const FName MainMenu = FName(TEXT("MainMenu"));
	const FName Hosting = FName(TEXT("Hosting"));
	const FName Joining = FName(TEXT("Joining"));
	const FName Playing = FName(TEXT("Playing"));
}

UTGCOGameInstance::UTGCOGameInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	CurrentState = TGCOGameInstanceState::None;
	ServerListObject = nullptr;
}


void UTGCOGameInstance::Init()
{
	Super::Init();

	// game requires the ability to ID users.
	const auto OnlineSub = IOnlineSubsystem::Get();
	check(OnlineSub);
	const auto IdentityInterface = OnlineSub->GetIdentityInterface();
	check(IdentityInterface.IsValid());

	const auto SessionInterface = OnlineSub->GetSessionInterface();
	check(SessionInterface.IsValid());

	OnlineSub->AddOnConnectionStatusChangedDelegate(FOnConnectionStatusChangedDelegate::CreateUObject(this, &UTGCOGameInstance::HandleNetworkConnectionStatusChanged));

	OnEndSessionCompleteDelegate = FOnEndSessionCompleteDelegate::CreateUObject(this, &UTGCOGameInstance::OnEndSessionComplete);
	
	// Register delegate for ticker callback
	TickDelegate = FTickerDelegate::CreateUObject(this, &UTGCOGameInstance::Tick);
	FTicker::GetCoreTicker().AddTicker(TickDelegate);
}

void UTGCOGameInstance::SetIsOnline(bool bInIsOnline)
{
	bIsOnline = bInIsOnline;
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		for (int32 i = 0; i < LocalPlayers.Num(); ++i)
		{
			ULocalPlayer* LocalPlayer = LocalPlayers[i];

			TSharedPtr<FUniqueNetId> PlayerId = LocalPlayer->GetPreferredUniqueNetId();
			if (PlayerId.IsValid())
			{
				OnlineSub->SetUsingMultiplayerFeatures(*PlayerId, bIsOnline);
			}
		}
	}
}

bool UTGCOGameInstance::GetIsOnline() const
{
	return bIsOnline;
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


void UTGCOGameInstance::ShowMessageThenGotoState(const FString& Message, const FName& NewState)
{
	UE_LOG(LogOnline, Log, TEXT("ShowMessageThenGotoState: Message: %s, NewState: %s"), *Message, *NewState.ToString());

	const bool bAtWelcomeScreen = PendingState == TGCOGameInstanceState::WelcomeScreen || CurrentState == TGCOGameInstanceState::WelcomeScreen;

	GotoState(NewState);
}

bool UTGCOGameInstance::HostGame(ULocalPlayer* LocalPlayer, const FString& InMapName)
{
	SetIsOnline(true);

	ATGCOGameSession* const GameSession = GetGameSession();
	if (GameSession)
	{
		// add callback delegate for completion
		GameSession->OnCreatePresenceSessionComplete().AddUObject(this, &UTGCOGameInstance::OnCreatePresenceSessionComplete);
	
		bool const bIsLanMatch = true;

		// Create the TraverURL from the MapName
		TravelURL = "/Game/Maps/" + InMapName;

		UE_LOG(LogOnline, Log, TEXT("MapName : %s"), *InMapName);
		UE_LOG(LogOnline, Log, TEXT("TravelURL : %s"), *TravelURL);

		if (GameSession->HostSession(LocalPlayer->GetPreferredUniqueNetId(), GameSessionName, InMapName, bIsLanMatch, true, ATGCOGameSession::DEFAULT_NUM_PLAYERS))
		{
			// If any error occured in the above, pending state would be set
			if ((PendingState == TGCOGameInstanceState::Hosting))
			{	
				return true;
			}
		}
	}

	return false;
	/**
	GotoState(TGCOGameInstanceState::Hosting);
	return true;
	*/
}

void UTGCOGameInstance::OnCreatePresenceSessionComplete(FName SessionName, bool bWasSuccessful)
{
	ATGCOGameSession* const GameSession = GetGameSession();
	if (GameSession)
	{
		GameSession->OnCreatePresenceSessionComplete().RemoveUObject(this, &UTGCOGameInstance::OnCreatePresenceSessionComplete);

		FinishSessionCreation(bWasSuccessful ? EOnJoinSessionCompleteResult::Success : EOnJoinSessionCompleteResult::UnknownError);
	}
}

void UTGCOGameInstance::FinishSessionCreation(EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		GotoState(TGCOGameInstanceState::Hosting);
	}
	else
	{
		ShowMessageThenGotoState(FString("CreateSessionFailed"), TGCOGameInstanceState::MainMenu);
	}
}

void UTGCOGameInstance::BeginServerSearch(ULocalPlayer* PlayerOwner)
{
	if (ServerListObject == nullptr)
	{
		ServerListObject = ConstructObject<UTGCOServerList>(UTGCOServerList::StaticClass());
		ServerListObject->Init(PlayerOwner);
	}

	ServerListObject->BeginServerSearch(true);
}

bool UTGCOGameInstance::FindSessions(ULocalPlayer* PlayerOwner, bool bFindLAN)
{
	SetIsOnline(true);
	bool bResult = false;

	check(PlayerOwner != nullptr);
	if (PlayerOwner)
	{
		ATGCOGameSession* const GameSession = GetGameSession();
		if (GameSession)
		{
			GameSession->OnFindSessionsComplete().RemoveAll(this);
			GameSession->OnFindSessionsComplete().AddUObject(this, &UTGCOGameInstance::OnSearchSessionsComplete);

			UE_LOG(LogOnline, Log, TEXT("Searching for GameSessionName = %s"), *GameSessionName.ToString());
			GameSession->FindSessions(PlayerOwner->GetPreferredUniqueNetId(), GameSessionName, bFindLAN, true);

			bResult = true;
		}
	}

	return bResult;
}

void UTGCOGameInstance::OnSearchSessionsComplete(bool bWasSuccessful)
{
	ATGCOGameSession* const Session = GetGameSession();
	if (Session)
	{
		Session->OnFindSessionsComplete().RemoveUObject(this, &UTGCOGameInstance::OnSearchSessionsComplete);
	}
}

void UTGCOGameInstance::OnServerSearchFinished()
{
	FString ServerName;
	if (ServerListObject != nullptr)
	{
		TArray<FServerEntry> ServerList = ServerListObject->GetServerList();
		int32 iNbServer = ServerList.Num();
		if (iNbServer > 0)
		{
			ServerName = ServerList[0].ServerName;
			//JoinSession(ServerListObject->GetPlayer().Get(), 0);
		}

		OnSearchCompleted.Broadcast(iNbServer);
	}
}

UTGCOServerList* UTGCOGameInstance::GetServerList() const
{
	return ServerListObject;
}

bool UTGCOGameInstance::JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults)
{
	ATGCOGameSession* const GameSession = GetGameSession();
	if (GameSession)
	{
		AddNetworkFailureHandlers();

		GameSession->OnJoinSessionComplete().AddUObject(this, &UTGCOGameInstance::OnJoinSessionComplete);
		if (GameSession->JoinSession(LocalPlayer->GetPreferredUniqueNetId(), GameSessionName, SessionIndexInSearchResults))
		{
			// If any error occured in the above, pending state would be set
			if ((PendingState == CurrentState) || (PendingState == TGCOGameInstanceState::None))
			{
				UE_LOG(LogOnlineGame, Verbose, TEXT("Return true on join session"));
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

void UTGCOGameInstance::OnJoinSessionComplete(EOnJoinSessionCompleteResult::Type Result)
{
	// unhook the delegate
	ATGCOGameSession* const GameSession = GetGameSession();
	if (GameSession)
	{
		GameSession->OnJoinSessionComplete().RemoveUObject(this, &UTGCOGameInstance::OnJoinSessionComplete);
	}

	FinishJoinSession(Result);
}

void UTGCOGameInstance::FinishJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		FString ReturnReason;
		switch (Result)
		{
		case EOnJoinSessionCompleteResult::RoomIsFull:
			ReturnReason = NSLOCTEXT("NetworkErrors", "JoinSessionFailed", "Game is full.").ToString();
			break;
		case EOnJoinSessionCompleteResult::RoomDoesNotExist:
			ReturnReason = NSLOCTEXT("NetworkErrors", "JoinSessionFailed", "Game no longer exists.").ToString();
			break;
		default:
			ReturnReason = NSLOCTEXT("NetworkErrors", "JoinSessionFailed", "Join failed.").ToString();
			break;
		}

		RemoveNetworkFailureHandlers();
		ShowMessageThenGotoState(ReturnReason, TGCOGameInstanceState::MainMenu);
		return;
	}
	InternalTravelToSession(GameSessionName);
}

void UTGCOGameInstance::InternalTravelToSession(const FName& SessionName)
{
	APlayerController * const PlayerController = GetFirstLocalPlayerController();

	if (PlayerController == nullptr)
	{
		FString ReturnReason = NSLOCTEXT("NetworkErrors", "InvalidPlayerController", "Invalid Player Controller").ToString();
		RemoveNetworkFailureHandlers();
		ShowMessageThenGotoState(ReturnReason, TGCOGameInstanceState::MainMenu);
		return;
	}

	// travel to session
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub == nullptr)
	{
		FString ReturnReason = NSLOCTEXT("NetworkErrors", "OSSMissing", "OSS missing").ToString();
		RemoveNetworkFailureHandlers();
		ShowMessageThenGotoState(ReturnReason, TGCOGameInstanceState::MainMenu);
		return;
	}

	FString URL;
	IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

	if (!Sessions.IsValid() || !Sessions->GetResolvedConnectString(SessionName, URL))
	{
		FString FailReason = NSLOCTEXT("NetworkErrors", "TravelSessionFailed", "Travel to Session failed.").ToString();
		ShowMessageThenGotoState(FailReason, TGCOGameInstanceState::MainMenu);
		UE_LOG(LogOnlineGame, Warning, TEXT("Failed to travel to session upon joining it"));
		return;
	}

	UE_LOG(LogOnlineGame, Verbose, TEXT("I'm here and URL is : %s"), *URL);
	
	ServerListObject = nullptr;

	PlayerController->ClientTravel(URL, TRAVEL_Absolute);
}

void UTGCOGameInstance::RemoveNetworkFailureHandlers()
{
	// Remove the local session/travel failure bindings if they exist
	if (GEngine->OnTravelFailure().IsBoundToObject(this) == true)
	{
		GEngine->OnTravelFailure().RemoveUObject(this, &UTGCOGameInstance::TravelLocalSessionFailure);
	}
}

void UTGCOGameInstance::AddNetworkFailureHandlers()
{
	// Add network/travel error handlers (if they are not already there)
	if (GEngine->OnTravelFailure().IsBoundToObject(this) == false)
	{
		GEngine->OnTravelFailure().AddUObject(this, &UTGCOGameInstance::TravelLocalSessionFailure);
	}
}

void UTGCOGameInstance::TravelLocalSessionFailure(UWorld *World, ETravelFailure::Type FailureType, const FString& ReasonString)
{
	/* TO DO
	AShooterPlayerController_Menu* const FirstPC = Cast<AShooterPlayerController_Menu>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (FirstPC != nullptr)
	{
		FString ReturnReason = NSLOCTEXT("NetworkErrors", "JoinSessionFailed", "Join Session failed.").ToString();
		if (ReasonString.IsEmpty() == false)
		{
			ReturnReason += " ";
			ReturnReason += ReasonString;
		}
		ShowMessageThenGotoState(ReturnReason, TGCOGameInstanceState::MainMenu);
	}
	*/
}

bool UTGCOGameInstance::Tick(float DeltaSeconds)
{
	MaybeChangeState();

	if (ServerListObject)
	{
		ServerListObject->Tick(DeltaSeconds);
	}

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
	UE_LOG(LogOnline, Log, TEXT("GotoState: NewState: %s"), *NewState.ToString());

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
	else if (CurrentState == TGCOGameInstanceState::Hosting)
	{
		EndHostingState();
	}
	else if (CurrentState == TGCOGameInstanceState::Joining)
	{
		EndJoiningState();
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
	else if (NewState == TGCOGameInstanceState::Hosting)
	{
		BeginHostingState();
	}
	else if (NewState == TGCOGameInstanceState::Joining)
	{
		BeginJoiningState();
	}

	CurrentState = NewState;
}

void UTGCOGameInstance::BeginMainMenuState()
{
	//UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("/Game/Maps/MainMenuMap")), true, FString(TEXT("listen")));
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("/Game/Maps/MainMenuMap")), true, FString());

	// player 0 gets to own the UI
	ULocalPlayer* const Player = GetFirstGamePlayer();
}

void UTGCOGameInstance::EndMainMenuState()
{

}

void UTGCOGameInstance::BeginPlayingState()
{
	GetWorld()->ServerTravel(FString("/Game/Maps/Room1"));
}

void UTGCOGameInstance::EndPlayingState()
{

}

void UTGCOGameInstance::BeginHostingState()
{
	//GetWorld()->ServerTravel(FString("/Game/Maps/HostMap?listen"));
	UGameplayStatics::OpenLevel(GetWorld(), FName(*TravelURL), true, FString(TEXT("listen")));
	//UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("/Game/Maps/HostMap")), true);
}

void UTGCOGameInstance::EndHostingState()
{
	CleanupSessionOnReturnToMenu();
}

void UTGCOGameInstance::BeginJoiningState()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("/Game/Maps/HostMap")), true);
}

void UTGCOGameInstance::EndJoiningState()
{

}

void UTGCOGameInstance::OnEndSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogOnline, Log, TEXT("UShooterGameInstance::OnEndSessionComplete: Session=%s bWasSuccessful=%s"), *SessionName.ToString(), bWasSuccessful ? TEXT("true") : TEXT("false"));

	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			Sessions->ClearOnStartSessionCompleteDelegate(OnEndSessionCompleteDelegate);
			Sessions->ClearOnEndSessionCompleteDelegate(OnEndSessionCompleteDelegate);
			Sessions->ClearOnDestroySessionCompleteDelegate(OnEndSessionCompleteDelegate);
		}
	}

	// continue
	CleanupSessionOnReturnToMenu();
}

void UTGCOGameInstance::CleanupSessionOnReturnToMenu()
{
	bool bPendingOnlineOp = false;

	// end online game and then destroy it
	IOnlineSubsystem * OnlineSub = IOnlineSubsystem::Get();
	IOnlineSessionPtr Sessions = (OnlineSub != NULL) ? OnlineSub->GetSessionInterface() : NULL;

	if (Sessions.IsValid())
	{
		EOnlineSessionState::Type SessionState = Sessions->GetSessionState(GameSessionName);
		UE_LOG(LogOnline, Log, TEXT("Session %s is '%s'"), *GameSessionName.ToString(), EOnlineSessionState::ToString(SessionState));

		if (EOnlineSessionState::InProgress == SessionState)
		{
			UE_LOG(LogOnline, Log, TEXT("Ending session %s on return to main menu"), *GameSessionName.ToString());
			Sessions->AddOnEndSessionCompleteDelegate(OnEndSessionCompleteDelegate);
			Sessions->EndSession(GameSessionName);
			bPendingOnlineOp = true;
		}
		else if (EOnlineSessionState::Ending == SessionState)
		{
			UE_LOG(LogOnline, Log, TEXT("Waiting for session %s to end on return to main menu"), *GameSessionName.ToString());
			Sessions->AddOnEndSessionCompleteDelegate(OnEndSessionCompleteDelegate);
			bPendingOnlineOp = true;
		}
		else if (EOnlineSessionState::Ended == SessionState || EOnlineSessionState::Pending == SessionState)
		{
			UE_LOG(LogOnline, Log, TEXT("Destroying session %s on return to main menu"), *GameSessionName.ToString());
			Sessions->AddOnDestroySessionCompleteDelegate(OnEndSessionCompleteDelegate);
			Sessions->DestroySession(GameSessionName);
			bPendingOnlineOp = true;
		}
		else if (EOnlineSessionState::Starting == SessionState)
		{
			UE_LOG(LogOnline, Log, TEXT("Waiting for session %s to start, and then we will end it to return to main menu"), *GameSessionName.ToString());
			Sessions->AddOnStartSessionCompleteDelegate(OnEndSessionCompleteDelegate);
			bPendingOnlineOp = true;
		}
	}

	if (!bPendingOnlineOp)
	{
		//GEngine->HandleDisconnect( GetWorld(), GetWorld()->GetNetDriver() );
	}
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

void UTGCOGameInstance::HandleNetworkConnectionStatusChanged(EOnlineServerConnectionStatus::Type ConnectionStatus)
{
	UE_LOG(LogOnlineGame, Warning, TEXT("UTGCOGameInstance::HandleNetworkConnectionStatusChanged: %s"), EOnlineServerConnectionStatus::ToString(ConnectionStatus));
}
