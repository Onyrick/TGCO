
#include "TGCO.h"
#include "PlayerStatus.h"

FString GetNameOfThePlayerStatus(const EPlayerStatus::State PlayerStatus)
{
	switch (PlayerStatus)
	{
		case EPlayerStatus::IN_GAME:					return TEXT("In game");
		case EPlayerStatus::IN_PUZZLE_GAME:				return TEXT("In puzzle game");
		case EPlayerStatus::IN_MENU_GAME:				return TEXT("In menu game");
		case EPlayerStatus::IN_INVENTORY_GAME:			return TEXT("In inventory game");
		default:										return TEXT("Unknown");
	}
}
