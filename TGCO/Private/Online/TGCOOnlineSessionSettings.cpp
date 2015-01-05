#include "TGCO.h"
#include "TGCOOnlineSessionSettings.h"


FTGCOOnlineSessionSettings::FTGCOOnlineSessionSettings(int32 MaxNumPlayers)
{
	NumPublicConnections = MaxNumPlayers;
	NumPrivateConnections = 0;
	bIsLANMatch = true;
	bShouldAdvertise = true;
	bAllowJoinInProgress = true;
	bAllowInvites = true;
	bUsesPresence = true;
	bAllowJoinViaPresence = true;
	bAllowJoinViaPresenceFriendsOnly = false;
}

FTGCOOnlineSearchSettings::FTGCOOnlineSearchSettings()
{
	bIsLanQuery = true;
	MaxSearchResults = 10;
	PingBucketSize = 50;

	QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
}
