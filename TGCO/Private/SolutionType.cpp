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
		case ESolutionType::RIGIDIFY:				return TEXT("Rigidify");
		default:									return TEXT("Unknown");
	}

}
