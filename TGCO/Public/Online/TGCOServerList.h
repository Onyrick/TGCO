
#pragma once

#include "Object.h"
#include "TGCOGameSession.h"
#include "TGCOServerList.generated.h"

USTRUCT(BlueprintType)
struct FServerEntry
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Server")
	FString ServerName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Server")
	FString CurrentPlayers;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Server")
	FString MaxPlayers;
	FString Ping;
	int32 SearchResultsIndex;
};

/**
 * @brief Manage all servers reachable
 */
UCLASS()
class TGCO_API UTGCOServerList : public UObject
{
	GENERATED_BODY()
public:
	UTGCOServerList(const FObjectInitializer& ObjectInitializer);

	/** @brief Init the object with the Player that own it */
	void UTGCOServerList::Init(TWeakObjectPtr<class ULocalPlayer> pPlayer);

	/**
	 * @brief Get the current game session
	 *
	 * @return The current game session
	 */
	ATGCOGameSession* GetGameSession() const;

	/**
	 * @brief Get the current player that own this object
	 *
	 * @return The current player
	 */
	TWeakObjectPtr<class ULocalPlayer> GetPlayer() const;

	/**
	 * @brief Tick called by the GameInstance when needed
	 * 		  
	 * @param DeltaSecond Delta time
	 */
	void Tick(float DeltaSeconds);

	/** @brief Updates current search status */
	void UpdateSearchStatus();

	/** 
	* @brief Starts searching for servers  
	*  
	*  @param bLANMatch In LAN ?
	*/
	void BeginServerSearch(bool bLANMatch);

	/** @brief Called when server search is finished */
	void OnServerSearchFinished();

	/** @brief Fill/update server list */
	void UpdateServerList();

	/**    
	* @brief Connect to chosen server
	* 
	* @param SessionIndex The index of the chosen session
	*/
	UFUNCTION(BlueprintCallable, Category = "Server")
	void ConnectToServer(int32 SessionIndex);

	/**
	* @brief Get the list of servers
	*
	* @return TArray<FServerEntry> Array  of servers
	*/
	UFUNCTION(BlueprintCallable, Category = "Server")
	TArray<FServerEntry> GetServerList();

protected:
	/** Whether last searched for LAN */
	bool bLANMatchSearch;

	/** Whether we're searching for servers */
	bool bSearchingForServers;

	/** action bindings array */
	TArray<FServerEntry> ServerList;

	/** pointer to our owner PC */
	TWeakObjectPtr<class ULocalPlayer> PlayerOwner;
	
};
