

#pragma once
#include "BarrierColor.generated.h"

/**
* @enum EBarrierColor
*
* @brief List of all the colors that the @ref LightningBarrier can take
* Those colors are also used by the @ref LightningSwitch to know which barriers
* they control
*/

UENUM(BlueprintType)
enum class EBarrierColor : uint8
{
	VE_Blue		UMETA(DisplayName = "Blue"),
	VE_Green 	UMETA(DisplayName = "Green"),
	VE_Orange 	UMETA(DisplayName = "Orange"),
	VE_Yellow 	UMETA(DisplayName = "Yellow"),
	VE_Red	 	UMETA(DisplayName = "Red"),
	VE_Purple 	UMETA(DisplayName = "Purple")
};

/**
* Return the color of the barrier
*
* @param BarrierColor value of the enum EBarrierColor
* @return FColor color of the barrier
*/

FColor GetBarrierColor(const EBarrierColor BarrierColor);

