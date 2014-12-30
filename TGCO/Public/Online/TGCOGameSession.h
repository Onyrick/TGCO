// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

protected:
	/** Transient properties of a session during game creation/matchmaking */
	FTGCOGameSessionsParams CurrentSessionParams;

public:
	/** Default number of players allowed in a game */
	static const int32 DEFAULT_NUM_PLAYERS = 2;
	
	
};
