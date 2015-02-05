// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

namespace ESolutionType
{
	/** List of solution type */
	UENUM(BlueprintType)
	enum class Type : uint8
	{
		ACID UMETA(DisplayName = "Acid"),
		CAUSTIC_SODA UMETA(DisplayName = "Caustic Soda"),
		SALTED_WATER UMETA(DisplayName = "Salted Water"),
		ETHANOL UMETA(DisplayName = "Ethanol"),
		MERCURY UMETA(DisplayName = "Mercury"),
		WEEDKILLING UMETA(DisplayName = "Weedkilling"),
		INFLAMMABLE_PRODUCT UMETA(DisplayName = "Inflammable"),
		FROZEN_PRODUCT UMETA(DisplayName = "Frozen Product"),
		NITROGLYCERINE UMETA(DisplayName = "Nitroglycerine"),
		RIGIDIFY UMETA(DisplayName = "Rigidify")
	};
}

/**
 * Return the name of the solution type
 *
 * @param SolutionType value of the enum ESolutionType
 *
 * @return FString string of the solution type
 */
FString GetNameOfTheSolution(const ESolutionType::Type SolutionType);
