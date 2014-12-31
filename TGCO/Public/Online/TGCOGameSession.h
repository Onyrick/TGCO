// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Online.h"
#include "GameFramework/GameSession.h"
#include "TGCOGameSession.generated.h"

struct FTGCOGameSessionsParams
{
	/** Name of session settings are stored with */
	FName SessionName;
	/** LAN Session */
	bool bIsLAN;
	/** Presence enabled session */
	bool bIsPresence;
	/** Id of player initiating lobby */
	TSharedPtr<FUniqueNetId> UserId;
	/** Current search result choice to join */
	int32 iBestSessionIdx;

	FTGCOGameSessionsParams()
		: SessionName(NAME_None)
		, bIsLAN(false)
		, bIsPresence(false)
		, iBestSessionIdx(0)
	{
	}
};

/**
 * 
 */
UCLASS(config = Game)
class TGCO_API ATGCOGameSession : public AGameSession
{
	GENERATED_UCLASS_BODY()
public:

	/**
	* Host a new online session
	*
	* @param UserId user that initiated the request
	* @param SessionName name of session
	* @param bIsLAN is this going to hosted over LAN
	* @param bIsPresence is the session to create a presence session
	* @param MaxNumPlayers Maximum number of players to allow in the session
	*
	* @return bool true if successful, false otherwise
	*/
	bool HostSession(TSharedPtr<FUniqueNetId> UserId, FName SessionName, const FString& MapName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	/** Test functions for BP */
	UFUNCTION(BlueprintCallable, Category = "Test")
	FString GetPlayerUniqueId();

	UFUNCTION(BlueprintCallable, Category = "Test")
	FName GetSessionName();

public:
	/** Default number of players allowed in a game */
	static const int32 DEFAULT_NUM_PLAYERS = 2;

protected:
	/** Transient properties of a session during game creation/matchmaking */
	FTGCOGameSessionsParams CurrentSessionParams;
	/** Current host settings */
	TSharedPtr<class FTGCOOnlineSessionSettings> HostSettings;
	/** Current search settings */
	//TSharedPtr<class FShooterOnlineSearchSettings> SearchSettings;
	
};
