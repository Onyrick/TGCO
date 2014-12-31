
#pragma once

#include "Online.h"

/**
* General session settings for TGCO
*/
class FTGCOOnlineSessionSettings : public FOnlineSessionSettings
{
public:

	FTGCOOnlineSessionSettings(bool bIsLAN = false, bool bIsPresence = false, int32 MaxNumPlayers = 2);
	virtual ~FTGCOOnlineSessionSettings() {};
};

