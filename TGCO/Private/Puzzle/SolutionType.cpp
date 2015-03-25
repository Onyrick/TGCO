
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
		/*case ESolutionType::INFLAMMABLE_PRODUCT:	return TEXT("Inflammable product");
		case ESolutionType::FROZEN_PRODUCT:			return TEXT("Frozen product");
		case ESolutionType::NITROGLYCERINE:			return TEXT("Nitroglycerine");
		case ESolutionType::RIGIDIFY:				return TEXT("Rigidify");*/
		default:									return TEXT("Unknown");
	}

}

ESolutionType::Type GetSolutionFromInt(int iNumber)
{
	switch (iNumber)
	{
		case 0:									return ESolutionType::ACID;
		case 1: 								return ESolutionType::CAUSTIC_SODA;
		case 2: 								return ESolutionType::SALTED_WATER;
		case 3: 								return ESolutionType::ETHANOL;
		case 4: 								return ESolutionType::MERCURY;
		case 5: 								return ESolutionType::WEEDKILLING;
		/*case 6: 								return ESolutionType::INFLAMMABLE_PRODUCT;
		case 7: 								return ESolutionType::FROZEN_PRODUCT;
		case 8: 								return ESolutionType::NITROGLYCERINE;
		case 9: 								return ESolutionType::RIGIDIFY;*/
		default:								return ESolutionType::ACID;
	}
}

int GetNumberOfSolution()
{
	return 10;
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
	/*case ESolutionType::INFLAMMABLE_PRODUCT:	return FColor(128, 30, 30);
	case ESolutionType::FROZEN_PRODUCT:			return FColor(91, 144, 172);
	case ESolutionType::NITROGLYCERINE:			return FColor(255, 0, 255);
	case ESolutionType::RIGIDIFY:				return FColor(0, 0, 0);*/
	default:									return FColor(0, 0, 0);
	}
}
