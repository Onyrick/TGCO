

#pragma once
#include "BarrierColor.generated.h"

/**
 *
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

FColor GetBarrierColor(const EBarrierColor BarrierColor);

