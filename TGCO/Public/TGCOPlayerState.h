

#pragma once

#include "GameFramework/PlayerState.h"
#include "TGCOPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API ATGCOPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ATGCOPlayerState(const FObjectInitializer& ObjectInitializer);

	/** Return PlayerNumber 
	* @return PlayerNumber number of the player
	*/
	UFUNCTION(BlueprintCallable, Category = "Online")
	int32 GetPlayerNumber();

	/** Set PlayerNumber */
	UFUNCTION(BlueprintCallable, Category = "Online")
	void SetPlayerNumber(int32 NewPlayerNumber);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Online")
	void ServerSetPlayerNumber(int32 NewPlayerNumber);

protected:
	/** Player number (0 = Maximilien = futur / 1 = Samantha = past */
	UPROPERTY(Replicated)
	int32 PlayerNumber;
	
};
