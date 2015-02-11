#include "TGCO.h"
#include "DiodeColor.h"

FString GetColorOfTheDiode(const EDiodeColor::Color DiodeColor)
{
	switch (DiodeColor)
	{
	case EDiodeColor::WHITE:					return TEXT("White");
	case EDiodeColor::RED:						return TEXT("Red");
	case EDiodeColor::BLUE:						return TEXT("Blue");
	case EDiodeColor::GREEN:					return TEXT("Green");
	case EDiodeColor::ORANGE:					return TEXT("Orange");
	default:									return TEXT("Unknown");
	}
}
