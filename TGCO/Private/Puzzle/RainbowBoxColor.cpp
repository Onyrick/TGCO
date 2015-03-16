

#include "TGCO.h"
#include "RainbowBoxColor.h"

float GetRedValueOfTheColor(const ERainbowBoxColor::Color RainbowBoxColor)
{
	switch (RainbowBoxColor)
	{
		case ERainbowBoxColor::NONE:					return 0.0;
		case ERainbowBoxColor::RED:						return 1.0;
		case ERainbowBoxColor::GREEN:					return 0.0;
		case ERainbowBoxColor::BLUE:					return 0.0;
		default:										return 0.0;
	}
}

float GetGreenValueOfTheColor(const ERainbowBoxColor::Color RainbowBoxColor)
{
	switch (RainbowBoxColor)
	{
		case ERainbowBoxColor::NONE:					return 0.0;
		case ERainbowBoxColor::RED:						return 0.0;
		case ERainbowBoxColor::GREEN:					return 1.0;
		case ERainbowBoxColor::BLUE:					return 0.0;
		default:										return 0.0;
	}
}

float GetBlueValueOfTheColor(const ERainbowBoxColor::Color RainbowBoxColor)
{
	switch (RainbowBoxColor)
	{
		case ERainbowBoxColor::NONE:					return 0.0;
		case ERainbowBoxColor::RED:						return 0.0;
		case ERainbowBoxColor::GREEN:					return 0.0;
		case ERainbowBoxColor::BLUE:					return 1.0;
		default:										return 0.0;
	}
}

FName GetNameOfTheColor(const ERainbowBoxColor::Color RainbowBoxColor){
	switch (RainbowBoxColor)
	{
		case ERainbowBoxColor::NONE:					return TEXT("None");
		case ERainbowBoxColor::RED:						return TEXT("Red");
		case ERainbowBoxColor::GREEN:					return TEXT("Green");
		case ERainbowBoxColor::BLUE:					return TEXT("Blue");
		default:										return TEXT("None");
	}
}

ERainbowBoxColor::Color GetColorFromInt(int iColor)
{
	switch (iColor)
	{
	case 0:										return ERainbowBoxColor::NONE;
	case 1:										return ERainbowBoxColor::RED;
	case 2:										return ERainbowBoxColor::GREEN;
	case 3:										return ERainbowBoxColor::BLUE;
	default:										return ERainbowBoxColor::NONE;
	}
}

int GetIntFromColor(ERainbowBoxColor::Color RainbowBoxColor)
{
	switch (RainbowBoxColor)
	{
	case ERainbowBoxColor::NONE:					return 0;
	case ERainbowBoxColor::RED:						return 1;
	case ERainbowBoxColor::GREEN:					return 2;
	case ERainbowBoxColor::BLUE:					return 3;
	default:										return 0;
	}
}
