
#pragma once

#include "ShootMode.generated.h"

/**
* @namespace	EShootMode
*
* @brief	Contain the enum of shoot modes type
*/
UENUM(BlueprintType)
namespace EShootMode
{
	/** @brief	Values that represent projectile types. */
	enum Type
	{
		NONE UMETA(DisplayName = "None"),
		SLOW UMETA(DisplayName = "Slow"),
		SPEED UMETA(DisplayName = "Speed"),
		STOP UMETA(DisplayName = "Stop"),
	};
}

/**
* @brief   Return the energy that the current projectile mode consumed
*
* @param   ShootMode    value of the enum EShootMode
*
* @return  int          amount consumed by the mode
*/
int GetEnergyConsuming(const EShootMode::Type ShootMode);

/**
* @brief   Return the name of the shoot mode
*
* @param   ShootMode    value of the enum EShootMode
* 						
* @return  FString      string of the shoot mode
*/
FString GetNameOfTheMode(const EShootMode::Type ShootMode);

/**
* Return the name of the shoot mode
*
* @param ShootMode value of the enum EShootMode
* @return FColor color of the shoot mode
*/
FColor GetColorOfTheMode(const EShootMode::Type ShootMode);
