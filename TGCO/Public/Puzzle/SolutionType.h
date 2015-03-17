
#pragma once

#include "SolutionType.generated.h"

/**
* @namespace	ESolutionType
*
* @brief	Contain the enum of solution type
*/
UENUM(BlueprintType)
namespace ESolutionType
{
	/**
	* @enum	Type
	*
	* @brief	List of solution type
	*/
	enum Type
	{
		NONE UMETA(DisplayName = "None"),
		ACID UMETA(DisplayName = "Acid"),
		CAUSTIC_SODA UMETA(DisplayName = "Caustic Soda"),
		SALTED_WATER UMETA(DisplayName = "Salted Water"),
		ETHANOL UMETA(DisplayName = "Ethanol"),
		MERCURY UMETA(DisplayName = "Mercury"),
		WEEDKILLING UMETA(DisplayName = "Weedkilling"),
		INFLAMMABLE_PRODUCT UMETA(DisplayName = "Inflammable"),
		FROZEN_PRODUCT UMETA(DisplayName = "Frozen Product"),
		NITROGLYCERINE UMETA(DisplayName = "Nitroglycerine"),
		RIGIDIFY UMETA(DisplayName = "Rigidify"),
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
/**
* Return the color of the solution type
*
* @param SolutionType value of the enum ESolutionType
*
* @return FColor color of the solution type
*/
FColor GetColorOfTheSolution(const ESolutionType::Type SolutionType);
