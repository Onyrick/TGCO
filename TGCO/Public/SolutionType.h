// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

namespace ESolutionType
{
	/** List of solution type */
	enum Type
	{
		ACID,
		CAUSTIC_SODA,
		SALTED_WATER,
		ETHANOL,
		MERCURY,
		WEEDKILLING,
		INFLAMMABLE_PRODUCT,
		FROZEN_PRODUCT,
		NITROGLYCERINE,
		RIGIDIFY
	};
}

/**
 * Return the name of the solution type
 *
 * @param SolutionType value of the enum ESolutionType
 * @return FString string of the solution type
 */
FString GetNameOfTheSolution(const ESolutionType::Type SolutionType);

/**
* Return a solution type according a number
*
* @param int the number required
* @return ESolutionType::Type the required SolutionType
*/
ESolutionType::Type GetSolutionFromInt(int iNumber);

/**
* Return the number of solutions
* @return int number of solutions
*/
int GetNumberOfSolution();
