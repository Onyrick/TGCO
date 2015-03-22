
#include "TGCO.h"
#include "TGCOServerList.h"
#include "TGCOGameInstance.h"

UTGCOServerList::UTGCOServerList(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, bLANMatchSearch(false)
, bSearchingForServers(false)
, PlayerOwner(nullptr)
{}

void UTGCOServerList::Init(TWeakObjectPtr<class ULocalPlayer> pPlayer)
{
	PlayerOwner = pPlayer;
}

ATGCOGameSession* UTGCOServerList::GetGameSession() const
{
	UTGCOGameInstance* const GI = Cast<UTGCOGameInstance>(PlayerOwner->GetGameInstance());
	return GI ? GI->GetGameSession() : nullptr;
}

void UTGCOServerList::UpdateSearchStatus()
{
	check(bSearchingForServers); // should not be called otherwise

	bool bFinishSearch = true;
	ATGCOGameSession* Session = GetGameSession();
	if (Session)
	{
		int32 CurrentSearchIdx, NumSearchResults;
		EOnlineAsyncTaskState::Type SearchState = Session->GetSearchResultStatus(CurrentSearchIdx, NumSearchResults);

		switch (SearchState)
		{
			case EOnlineAsyncTaskState::InProgress:
				bFinishSearch = false;
			break;

			case EOnlineAsyncTaskState::Done:
				// copy the results
				{
					ServerList.Empty();
					const TArray<FOnlineSessionSearchResult> & SearchResults = Session->GetSearchResults();
					check(SearchResults.Num() == NumSearchResults);

					for (int32 IdxResult = 0; IdxResult < NumSearchResults; ++IdxResult)
					{
						FServerEntry NewServerEntry;

						const FOnlineSessionSearchResult& Result = SearchResults[IdxResult];

						NewServerEntry.ServerName = Result.Session.OwningUserName;
						NewServerEntry.Ping = FString::FromInt(Result.PingInMs);
						NewServerEntry.CurrentPlayers = FString::FromInt(Result.Session.SessionSettings.NumPublicConnections
							+ Result.Session.SessionSettings.NumPrivateConnections
							- Result.Session.NumOpenPublicConnections
							- Result.Session.NumOpenPrivateConnections);
						NewServerEntry.MaxPlayers = FString::FromInt(Result.Session.SessionSettings.NumPublicConnections
							+ Result.Session.SessionSettings.NumPrivateConnections);
						NewServerEntry.SearchResultsIndex = IdxResult;
						
						ServerList.Add(NewServerEntry);
					}
				}
			break;

			case EOnlineAsyncTaskState::Failed:
			case EOnlineAsyncTaskState::NotStarted:
			default:
			break;
		}
	}

	if (bFinishSearch)
	{
		OnServerSearchFinished();
	}
}

void UTGCOServerList::Tick(float DeltaSeconds)
{
	if (bSearchingForServers == true)
	{
		UpdateSearchStatus();
	}
}

void UTGCOServerList::BeginServerSearch(bool bLANMatch)
{
	bLANMatchSearch = bLANMatch;
	bSearchingForServers = true;
	ServerList.Empty();

	UTGCOGameInstance* const GI = Cast<UTGCOGameInstance>(PlayerOwner->GetGameInstance());
	if (GI)
	{
		GI->FindSessions(PlayerOwner.Get(), bLANMatchSearch);
	}
}

void UTGCOServerList::OnServerSearchFinished()
{
	UE_LOG(LogOnline, Log, TEXT("Set SearchingServer to false"));
	bSearchingForServers = false;
	
	UTGCOGameInstance* const GI = Cast<UTGCOGameInstance>(PlayerOwner->GetGameInstance());
	if (GI)
	{
		GI->OnServerSearchFinished();
	}

	UpdateServerList();
}

void UTGCOServerList::UpdateServerList()
{
	// TODO : auto and not in BP ?
}

void UTGCOServerList::ConnectToServer(int32 SessionIndex)
{
	if (bSearchingForServers)
	{
		return;
	}

	UTGCOGameInstance* const GI = Cast<UTGCOGameInstance>(PlayerOwner->GetGameInstance());
	if (GI)
	{
		GI->JoinSession(PlayerOwner.Get(), SessionIndex);
	}
}

TArray<FServerEntry> UTGCOServerList::GetServerList()
{
	return ServerList;
}

TWeakObjectPtr<class ULocalPlayer> UTGCOServerList::GetPlayer() const
{
	return PlayerOwner;
}
