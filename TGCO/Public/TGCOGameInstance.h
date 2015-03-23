
#pragma once

#include "Engine/GameInstance.h"
#include "TGCOGameSession.h"
#include "TGCOServerList.h"
#include "TGCOGameInstance.generated.h"

/**
* @namespace TGCOGameInstanceState
* 
* @brief Store String of game state
*/
namespace TGCOGameInstanceState
{
	extern const FName None;
	extern const FName WelcomeScreen;
	extern const FName MainMenu;
	extern const FName Hosting;
	extern const FName Joining;
	extern const FName Playing;
}

/**
 * @brief GameInstance: high-level manager object for an instance of the running game. 
 * 		  Spawned at game creation and not destroyed until game instance is shut down. 
 * 		  Running as a standalone game, there will be one of these.
 * 		  Manage the state of the game.
 */
UCLASS(config = Game)
class TGCO_API UTGCOGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	UTGCOGameInstance(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief	Tick function.
	 *
	 * @param	DeltaSeconds	The delta in seconds.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */
	bool Tick(float DeltaSeconds);

	/**
	* @brief	Get the game session. 
	* 
	* @return ATGCOGameSession* The game session
	*/
	UFUNCTION(BlueprintCallable, Category = "Online")
	class ATGCOGameSession* GetGameSession() const;

	/**
	* @brief	Get the list of reachable servers.
	*
	* @return UTGCOServerList* The list of reachable servers
	*/
	UFUNCTION(BlueprintCallable, Category = "Server")
	class UTGCOServerList* GetServerList() const;

	/** @brief	Init he game instance. */
	virtual void Init() override;
	/** @brief	Shuts down the game instance. */
	virtual void Shutdown() override;
	/** @brief	Starts game instance. */
	virtual void StartGameInstance() override;

	/** @brief Start the game */
	UFUNCTION(BlueprintCallable, Category = "Online")
	void StartGame();

	/**   
	* @brief Host a game session 
	* 
	* @param	LocalPlayer	If non-null, the local player.
	* @param	InMapName		   	Name of the in map.
	*
	* @return	true if it succeeds, false if it fails.
	*/
	UFUNCTION(BlueprintCallable, Category = "Online")
	bool HostGame(ULocalPlayer* LocalPlayer, const FString& InMapName);

	/**
	 * @brief	Join a game session.
	 *
	 * @param   LocalPlayer		   	If non-null, the local player.
	 * @param	SessionIndexInSearchResults	The session index to join.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */
	UFUNCTION(BlueprintCallable, Category = "Online")
	bool JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults);

	/**
	* @brief Begin the server search 
	* 		
	* @param LocalPlayer		   	If non-null, the local player.
	*/
	UFUNCTION(BlueprintCallable, Category = "Online")
	void BeginServerSearch(ULocalPlayer* PlayerOwner);

	/** @brief End the server search auto */
	void OnServerSearchFinished();

	/**  
	* @brief Initiates the session searching 
	*
	* @param 	 LocalPlayer		If non-null, the local player. 	
	* @param 	 bLANMatch		   	Is it in a local network 	
	*
	* @return	true if it succeeds, false if it fails.	 
	*/
	UFUNCTION(BlueprintCallable, Category = "Online")
	bool FindSessions(ULocalPlayer* PlayerOwner, bool bLANMatch);

	/**   
	* @brief Sends the game to the specified state. 
	* 
	* @param NewState State to go
	*/
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void GotoState(FName NewState);

	/**   
	* @brief Obtains the initial welcome state, which can be different based on platform 
	* 	
	* @return FName Value of the initial state	 
	*/
	UFUNCTION(BlueprintCallable, Category = "GameState")
	FName GetInitialState();

	/** @brief Sends the game to the initial startup/frontend state  */
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void GotoInitialState();

	/**   
	* @brief Get curent state 
	* 
	* @return FName String of the current state
	*/
	UFUNCTION(BlueprintCallable, Category = "GameState")
	FName GetState();

	/**   
	* @brief Set current stage (be carefull when you use it) 
	* 
	* @param NewState The new state
	*/
	void SetCurrentState(FName NewState);

	/**
	 * @brief Creates the message menu, clears other menus and sets the KingState to Message.
	 *
	 * @param	Message				Main message body
	 * @param	NewState			Final state to go to when message is discarded
	 */
	void ShowMessageThenGotoState(const FString& Message, const FName& NewState);

	/** @brief Shuts down the session, and frees any net driver */
	UFUNCTION(BlueprintCallable, Category = "Online")
	void CleanupSessionOnReturnToMenu();

	/** @brief Trim the PC id to remove all after _ or - (tricky)  
	*
	* @param Id The id to trim
	* 
	* @return FString The trimed id
	*/
	UFUNCTION(BlueprintCallable, Category = "Text")
	FString TrimId(FString Id);

	/** Event launched when server search is finished */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FBindableEvent_ServerSearchFinished,
			
	int32,
	NumberServerFound
	);

	/** Called when Server Search is finished */
	UPROPERTY(BlueprintAssignable, Category = "Online")
	FBindableEvent_ServerSearchFinished OnSearchCompleted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableEvent_GoingToPlay);
	/** Called when we are going to play */
	UPROPERTY(BlueprintAssignable, Category = "Online")
	FBindableEvent_GoingToPlay OnGoingToPlay;
	
private:
	/** Delegate for ending a session */
	FOnEndSessionCompleteDelegate OnEndSessionCompleteDelegate;

	/** Last connection status that was passed into the HandleNetworkConnectionStatusChanged hander */
	EOnlineServerConnectionStatus::Type	CurrentConnectionStatus;

	void HandleNetworkConnectionStatusChanged(EOnlineServerConnectionStatus::Type ConnectionStatus);

	void OnEndSessionComplete(FName SessionName, bool bWasSuccessful);

	void MaybeChangeState();
	void EndCurrentState(FName NextState);
	void BeginNewState(FName NewState, FName PrevState);

	/** Functions called on begin state */
	void BeginWelcomeScreenState();
	void BeginMainMenuState();
	void BeginPlayingState();
	void BeginJoiningState();
	void BeginHostingState();

	/** Functions called on ending state */
	void EndWelcomeScreenState();
	void EndMainMenuState();
	void EndPlayingState();
	void EndJoiningState();
	void EndHostingState();

	void AddNetworkTravelFailureHandlers();
	void AddNetworkFailureHandlers();
	void RemoveNetworkTravelFailureHandlers();
	void RemoveNetworkFailureHandlers();
	
	
	/** Called when there is a Network error */
	void HandleNetworkFailure(UWorld *World, UNetDriver *NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

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
	/** Current state of the game */
	FName CurrentState;
	/** Pending state of the game */
	FName PendingState;
	 
	FString TravelURL;

	/** Delegate for callbacks to Tick */
	FTickerDelegate TickDelegate;

	/** Object to manager server */
	UTGCOServerList* ServerListObject;
};
