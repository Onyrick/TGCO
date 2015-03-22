
#pragma once

#include "Online.h"

/**
* General session settings for TGCO
*/
class FTGCOOnlineSessionSettings : public FOnlineSessionSettings
{
public:

	FTGCOOnlineSessionSettings(int32 MaxNumPlayers = 2);
	virtual ~FTGCOOnlineSessionSettings() {};
};

/**
* General search setting for TGCO
*/
class FTGCOOnlineSearchSettings : public FOnlineSessionSearch
{
public:
	FTGCOOnlineSearchSettings();

	virtual ~FTGCOOnlineSearchSettings() {}
};
