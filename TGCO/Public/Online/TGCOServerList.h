// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "TGCOGameSession.h"
#include "TGCOServerList.generated.h"

struct FServerEntry
{
	FString ServerName;
	FString CurrentPlayers;
	FString MaxPlayers;
	FString Ping;
	int32 SearchResultsIndex;
};

/**
 * 
 */
UCLASS()
class TGCO_API UTGCOServerList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UTGCOServerList(class FObjectInitializer& ObjectInitializer);

	/** Init the object with the Player that own it */
	void UTGCOServerList::Init(TWeakObjectPtr<class ULocalPlayer> pPlayer);

	/**
	* Get the current game session
	*
	* @return The current game session
	*/
	ATGCOGameSession* GetGameSession() const;

	/**
	* Get the current player that own this object
	*
	* @return The current player
	*/
	TWeakObjectPtr<class ULocalPlayer> GetPlayer() const;

	/**
	* Tick called by the GameInstance when needed
	*/
	void Tick(float DeltaSeconds);

	/** Updates current search status */
	void UpdateSearchStatus();

	/** Starts searching for servers */
	void BeginServerSearch(bool bLANMatch);

	/** Called when server search is finished */
	void OnServerSearchFinished();

	/** fill/update server list */
	void UpdateServerList();

	/** connect to chosen server */
	void ConnectToServer();

	TArray< TSharedPtr<FServerEntry> > GetServerList();

protected:
	/** Whether last searched for LAN */
	bool bLANMatchSearch;

	/** Whether we're searching for servers */
	bool bSearchingForServers;

	/** action bindings array */
	TArray< TSharedPtr<FServerEntry> > ServerList;

	/** current status text */
	FString StatusText;

	/** pointer to our owner PC */
	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;
	
};
