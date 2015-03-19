
#pragma once

#include "PlayerStatus.generated.h"

/**
* @namespace	EPlayerStatus
*
* @brief	Contain the enum of player state
*/
UENUM(BlueprintType)
namespace EPlayerStatus
{
	/**
	* @enum	Type
	*
	* @brief	List of state
	*/
	enum State
	{
		IN_GAME					UMETA(DisplayName = "In game"),
		IN_PUZZLE_GAME			UMETA(DisplayName = "In puzzle game"),
		IN_MENU_GAME			UMETA(DisplayName = "In menu game"),
		IN_INVENTORY_GAME		UMETA(DisplayName = "In inventory game")
	};
}

/**
 * Return the name of the player state
 *
 * @param PlayerStatus value of the enum EPlayerStatus
 * @return FString string of the player state
 */
FString GetNameOfThePlayerStatus(const EPlayerStatus::State PlayerStatus);
