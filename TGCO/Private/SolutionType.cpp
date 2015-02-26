// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "SolutionType.h"

FString GetNameOfTheSolution(const ESolutionType::Type SolutionType)
{
	switch(SolutionType)
	{
		case ESolutionType::ACID:					return TEXT("Acid");
		case ESolutionType::CAUSTIC_SODA:			return TEXT("Caustic acid");
		case ESolutionType::SALTED_WATER:			return TEXT("Salted Water");
		case ESolutionType::ETHANOL:				return TEXT("Ethanol");
		case ESolutionType::MERCURY:				return TEXT("Mercury");
		case ESolutionType::WEEDKILLING:			return TEXT("Weedkilling");
		case ESolutionType::INFLAMMABLE_PRODUCT:	return TEXT("Inflammable product");
		case ESolutionType::FROZEN_PRODUCT:			return TEXT("Frozen product");
		case ESolutionType::NITROGLYCERINE:			return TEXT("Nitroglycerine");
		case ESolutionType::RIGIDIFY:			return TEXT("Rigidify");
		default:									return TEXT("Unknown");
	}

}

FColor GetColorOfTheSolution(const ESolutionType::Type SolutionType)
{
	switch (SolutionType)
	{
	case ESolutionType::ACID:					return FColor(226, 230, 93);
	case ESolutionType::CAUSTIC_SODA:			return FColor(255, 255, 255);
	case ESolutionType::SALTED_WATER:			return FColor(64, 141, 157);
	case ESolutionType::ETHANOL:				return FColor(216, 190, 36);
	case ESolutionType::MERCURY:				return FColor(237, 56, 1);
	case ESolutionType::WEEDKILLING:			return FColor(222, 222, 222);
	case ESolutionType::INFLAMMABLE_PRODUCT:	return FColor(128, 30, 30);
	case ESolutionType::FROZEN_PRODUCT:			return FColor(91, 144, 172);
	case ESolutionType::NITROGLYCERINE:			return FColor(255, 0, 255);
	case ESolutionType::RIGIDIFY:				return FColor(0, 0, 0);
	default:									return FColor(0, 0, 0);
	}
}