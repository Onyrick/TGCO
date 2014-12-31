// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOGameSession.h"
#include "TGCOOnlineSessionSettings.h"

ATGCOGameSession::ATGCOGameSession(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool ATGCOGameSession::HostSession(TSharedPtr<FUniqueNetId> UserId, FName SessionName, const FString& MapName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		CurrentSessionParams.SessionName = SessionName;
		CurrentSessionParams.bIsLAN = bIsLAN;
		CurrentSessionParams.bIsPresence = bIsPresence;
		CurrentSessionParams.UserId = UserId;
		MaxPlayers = MaxNumPlayers;

		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid() && CurrentSessionParams.UserId.IsValid())
		{
			HostSettings = MakeShareable(new FTGCOOnlineSessionSettings(bIsLAN, bIsPresence, MaxPlayers));
			HostSettings->Set(SETTING_MAPNAME, MapName, EOnlineDataAdvertisementType::ViaOnlineService);
			HostSettings->Set(SETTING_SESSION_TEMPLATE_NAME, FString("GameSession"), EOnlineDataAdvertisementType::DontAdvertise);

			//Sessions->AddOnCreateSessionCompleteDelegate(OnCreateSessionCompleteDelegate);
			return Sessions->CreateSession(*CurrentSessionParams.UserId, CurrentSessionParams.SessionName, *HostSettings);
		}
	}

	return false;
}

FString ATGCOGameSession::GetPlayerUniqueId()
{
	return CurrentSessionParams.UserId->ToString();
}

FName ATGCOGameSession::GetSessionName()
{
	return CurrentSessionParams.SessionName; 
}
