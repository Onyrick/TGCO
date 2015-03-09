

#pragma once

#include "GameFramework/PlayerController.h"
#include "TGCOPlayerController.generated.h"

class AProps;
class AFan;
class ALightningBarrier;

/**
 * Interface between TGCOCharacter and the human player controlling it. 
 * ATGCOPlayerController essentially represents the human player's will.
 * The ATGCOPlayerController persists throughout the game
 */
UCLASS()
class TGCO_API ATGCOPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

public:
	/** Set game in pause */
	virtual bool SetPause(bool bPause, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

	/****** SERVER FUNCTIONS ******/
	
	/** 
	 * Function that update speed characteristic on a specific Props 
	 * Call on server by client
	 *
	 * @param	Props	Props for updating speed characteristic
	 */
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerUpdateSpeedOnProps(class AProps* Props);

	/**
	* Function that update the speed value on a specific Props
	* Call on server by client
	*
	* @param	Props	Props for updating speed value
	*/
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerUpdateSpeedValueOnProps(class AProps* Props, float fValue);
	
	/**
	* Function that change the activate state on a specific LightningBarrier
	* Call on server by client
	*
	* @param	LightningBarrier	LightningBarrier for updating State
	*/
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerChangeActiveStateOnBarrier(class ALightningBarrier* LightningBarrier, bool bValue);

	/**
	* Function that change the visibility of a mesh
	* Call on server by client
	*
	* @param	Mesh	Static Mesh for updating Visibility
	*/
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerUpdateVisibilityOnMesh(class UStaticMeshComponent* Mesh);

	/**
	* Function that update the speed characteristic on a specific Fan
	* Call on client by server
	*
	* @param	AFan	Fan for updating speed characteristic
	*			_fSpeed	The speed value
	*/
	UFUNCTION(Client, Reliable)
	void ClientAffectSpeedOnFutureFan(class AFan* Fan, float _fSpeed);
	
	/**
	* Function that activate a specific Fan
	* Call on server by client
	*
	* @param	AFan	Fan for activation
	*			bActive	Whether the Fan will be active
	*/
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerActivateFan(class AFan* Fan, bool bActive);

	/**
	* Function that decrease energy for players
	* Call on server by client
	*
	* @param	ATGCOGameState	GameState for decrease
	*			iEnergyAmount	The amount to decrease
	*			monsterHit		If decrease is due to monster
	*/
	UFUNCTION(Server, WithValidation, reliable)
	void ServerDecreaseEnergy(class ATGCOGameState* GameState, int32 iEnergyAmount, bool monsterHit = false);

	/**
	* Function that add energy for players
	* Call on server by client
	*
	* @param	ATGCOGameState	GameState for add
	*			iEnergyAmount	The amount to add
	*/
	UFUNCTION(Server, WithValidation, reliable)
	void ServerAddEnergy(class ATGCOGameState* GameState, int32 iEnergyAmount);

protected:
	/** Function call when the game start */
	virtual void BeginPlay() override;
	/** Function call every frame */
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	/** Set input for the Player Controller */
	virtual void SetupInputComponent() override;

private:
	void OnTogglePause();
};
