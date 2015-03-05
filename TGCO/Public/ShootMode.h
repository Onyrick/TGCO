// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootMode.generated.h"

UENUM(BlueprintType)
namespace EShootMode
{
	/** List of solution type */
	enum Type
	{
		NONE UMETA(DisplayName = "None"),
		SLOW UMETA(DisplayName = "Slow"),
		SPEED UMETA(DisplayName = "Speed"),
		STOP UMETA(DisplayName = "Stop"),
	};
}

/**
* Return the color of the solution type
*
* @param ShootMode value of the enum EShootMode
*
* @return int amount consumed by the mode
*/
int GetEnergyConsuming(const EShootMode::Type ShootMode);

/**
* Return the name of the solution type
*
* @param ShootMode value of the enum EShootMode
* @return FString string of the solution type
*/
FString GetNameOfTheMode(const EShootMode::Type ShootMode);
