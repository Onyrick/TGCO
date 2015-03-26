

#pragma once

#include "GameFramework/PlayerController.h"
#include "TGCOPlayerController.generated.h"

class AProps;
class AFan;
class ALightningBarrier;

/**
 * @brief	Interface between TGCOCharacter and the human player controlling it.
 * 			ATGCOPlayerController essentially represents the human player's will. The
 * 			ATGCOPlayerController persists throughout the game.
 */
UCLASS()
class TGCO_API ATGCOPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	ATGCOPlayerController(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief	Sets pause.
	 *
	 * @param	bPause			  	true to pause.
	 * @param	CanUnpauseDelegate	The function that can unpause.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */
	virtual bool SetPause(bool bPause, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	
	/**
	 * @brief	Function that update speed characteristic on a specific Props.
	 * 			Call on server by client.
	 *
	 * @param 	Props	Props for updating speed characteristic.
	 */
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerUpdateSpeedOnProps(class AProps* Props);

	/**
	 * @brief	Function that update the speed value on a specific Props.
	 * 			Call on server by client.
	 *
	 * @param 	Props	Props for updating speed value.
	 * @param	fValue		 	The value.
	 */
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerUpdateSpeedValueOnProps(class AProps* Props, float fValue);

	/**
	* @brief	Function that change the activate state on a specific LightningBarrier.
	* 			Call on server by client.
	*
	* @param 	LightningBarrier	LightningBarrier for updating active State.
	* @param	bValue						The value.
	*/
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerChangeActiveStateOnBarrier(class ALightningBarrier* LightningBarrier, bool bValue);

	/**
	* @brief	Function that set the deactivation code of the console in the lightning corridor
	*
	* @param 	AOpenBarrierConsole	AOpenBarrierConsole to receive the new code.
	* @param	code				The code.
	*/
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerSetOpeningCode(class AOpenBarrierConsole* OpenBarrierConsole, int32 code);

	/**
	 * @brief	Function that change the visibility of a mesh.
	 * 			Call on server by client.
	 *
	 * @param 	MinesweeperBox	Static Mesh for updating Visibility.
	 */
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerUpdateVisibilityOnMesh(class AMinesweeperBox* MinesweeperBox);

	/**
	 * @brief	Function that update the speed characteristic on a specific Fan.
	 * 			Call on client by server.
	 *
	 * @param 	Fan	Fan for updating speed characteristic.
	 * @param	_fSpeed	   	The speed.
	 */
	UFUNCTION(Client, Reliable)
	void ClientAffectSpeedOnFutureFan(class AFan* Fan, float _fSpeed);

	/**
	 * @brief	Function that activate a specific Fan.
	 * 			Call on server by client.
	 *
	 * @param 	Fan	Fan for activation.
	 * @param	bActive	   	Whether the Fan will be active.
	 */
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerActivateFan(class AFan* Fan, bool bActive);

	/**
	 * @brief	Function that decrease energy for players.
	 * 			Call on server by client.
	 *
	 * @param 	GameState	GameState for decrease.
	 * @param	iEnergyAmount	 	The amount to decrease.
	 * @param	monsterHit		 	If decrease is due to monster.
	 */
	UFUNCTION(Server, WithValidation, reliable)
	void ServerDecreaseEnergy(class ATGCOGameState* GameState, int32 iEnergyAmount, bool bCanPlayerDie = false);

	/**
	 * @brief	Function that add energy for players.
	 * 			Call on server by client.
	 *
	 * @param 	GameState	GameState for adding energy.
	 * @param	iEnergyAmount	 	The amount to add.
	 */
	UFUNCTION(Server, WithValidation, reliable)
	void ServerAddEnergy(class ATGCOGameState* GameState, int32 iEnergyAmount);

	/**
	* Function that activate a specific Fan
	* Call on server by client
	*
	* @param	AFan	Fan for activation
	*			bActive	Whether the Fan will be active
	*/
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerSetReadyToMove(class AMonster* Monster, bool _ready);

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerStunMonster(class AMonster* Monster);

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerDestroyMonster(class AMonstroPlante* Monster);

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerRespawnMonster(class AMonster* Monster);
	
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerSetNeedToAvoidMonster(class AMonstroPlante* Monster, bool _avoid);

protected:
	/** @brief   Function call when the game start */
	virtual void BeginPlay() override;

	/**
	 * @brief	Tick function for this actor.
	 *
	 * @param	DeltaTime					The delta time.
	 * @param	TickType					Type of the tick.
	 * @param 	ThisTickFunction	this tick function.
	 */
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	/** @brief  Set input for the Player Controller */
	virtual void SetupInputComponent() override;

private:
	/** @brief	Executes the toggle pause action. */
	void OnTogglePause();
};
