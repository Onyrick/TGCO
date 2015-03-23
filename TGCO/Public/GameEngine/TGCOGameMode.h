// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/GameMode.h"
#include "TGCOGameMode.generated.h"

/**
* @brief The GameMode defines the game being played. It governs the game rules, scoring, what actors are allowed to exist in this game type, and who may enter the game.
*/
UCLASS(minimalapi)
class ATGCOGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	ATGCOGameMode(const FObjectInitializer& ObjectInitializer);

	/** @brief	Function call at the beginning of the game. */
	virtual void StartPlay() override;

	/** @brief   Function called when Player is dead */
	void KillPlayersThenRespawn();

	UFUNCTION(Server, WithValidation, reliable)
	/** @brief	Server kill players then respawn. */
	void ServerKillPlayersThenRespawn();

protected:

	/**
	 * @brief	Gets game session class.
	 *
	 * @return	The game session class.
	 */
	virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;

private:

	/**
	 * @brief	Choose player start.
	 *
	 * @param   Player	If non-null, the player.
	 *
	 * @return	null if it fails, else an AActor*.
	 */
	virtual AActor* ChoosePlayerStart(AController* Player) override;

	/**
	 * @brief	Searches player start.
	 *
	 * @param   Player	If non-null, the player.
	 * @param	IncomingName  	Name of the incoming.
	 *
	 * @return	null if it fails, else the found player start.
	 */
	virtual AActor* FindPlayerStart( AController* Player, const FString& IncomingName = TEXT("") ) override;

	/**
	 * @brief	Restart player.
	 *
	 * @param   NewPlayer	If non-null, the new player to restart.
	 */
	virtual void RestartPlayer(AController* NewPlayer) override;
};
