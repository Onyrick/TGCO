// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "TGCOGameSession.h"
#include "TGCOServerList.h"
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

public:
	bool Tick(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Online")
	class ATGCOGameSession* GetGameSession() const;
	
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;

	/** Host a game session */
	UFUNCTION(BlueprintCallable, Category = "Online")
	bool HostGame(ULocalPlayer* LocalPlayer, const FString& InMapName);

	/** Join a game session */
	bool JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults);

//	bool JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult);

	/** Travel directly to the named session */
//	UFUNCTION(BlueprintCallable, Category = "Online")
//	void TravelToSession(const FName& SessionName);

	/** Begin the server search */
	UFUNCTION(BlueprintCallable, Category = "Online")
	void BeginServerSearch(ULocalPlayer* PlayerOwner);

	/** End the server search auto */
	void OnServerSearchFinished();

	/** Initiates the session searching */
	bool FindSessions(ULocalPlayer* PlayerOwner, bool bLANMatch);

	/** Sends the game to the specified state. */
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void GotoState(FName NewState);

	/** Obtains the initial welcome state, which can be different based on platform */
	UFUNCTION(BlueprintCallable, Category = "GameState")
	FName GetInitialState();

	/** Sends the game to the initial startup/frontend state  */
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void GotoInitialState();

	/**
	* Creates the message menu, clears other menus and sets the KingState to Message.
	*
	* @param	Message				Main message body
	* @param	NewState			Final state to go to when message is discarded
	*/
	void ShowMessageThenGotoState(const FString& Message, const FName& NewState);


	/** Shuts down the session, and frees any net driver */
	UFUNCTION(BlueprintCallable, Category = "Online")
	void CleanupSessionOnReturnToMenu();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
		FBindableEvent_ServerSearchFinished,
			
		FString,
		ServerName
	);

	/** Called when Server Search is finished */
	UPROPERTY(BlueprintAssignable, Category = "Online")
	FBindableEvent_ServerSearchFinished OnSearchCompleted;
	
private:
	/** Delegate for ending a session */
	FOnEndSessionCompleteDelegate OnEndSessionCompleteDelegate;

	void OnEndSessionComplete(FName SessionName, bool bWasSuccessful);

	void MaybeChangeState();
	void EndCurrentState(FName NextState);
	void BeginNewState(FName NewState, FName PrevState);

	void BeginWelcomeScreenState();
	void BeginMainMenuState();
	void BeginPlayingState();
	void BeginHostingState();

	void EndWelcomeScreenState();
	void EndMainMenuState();
	void EndPlayingState();
	void EndHostingState();

	void AddNetworkFailureHandlers();
	void RemoveNetworkFailureHandlers();
	
	/** Called when there is an error trying to travel to a local session */
	void TravelLocalSessionFailure(UWorld *World, ETravelFailure::Type FailureType, const FString& ErrorString);

	/** Callback which is intended to be called upon session creation */
	void OnCreatePresenceSessionComplete(FName SessionName, bool bWasSuccessful);
	
	/** Called after all the local players are registered */
	void FinishSessionCreation(EOnJoinSessionCompleteResult::Type Result);

	/** Callback which is intended to be called upon finding sessions */
	void OnSearchSessionsComplete(bool bWasSuccessful);

	/** Callback which is intended to be called upon joining session */
	void OnJoinSessionComplete(EOnJoinSessionCompleteResult::Type Result);

	/** Called after all the local players are registered in a session we're joining */
	void FinishJoinSession(EOnJoinSessionCompleteResult::Type Result);

	/** Travel directly to the named session */
	void InternalTravelToSession(const FName& SessionName);

private:
	FName CurrentState;
	FName PendingState;

	FString TravelURL;

	/** Delegate for callbacks to Tick */
	FTickerDelegate TickDelegate;

	/** Object to manager server */
	UTGCOServerList* ServerListObject;
};