
#include "TGCO.h"
#include "ShootMode.h"

int GetEnergyConsuming(const EShootMode::Type ShootMode)
{
	switch (ShootMode)
	{
		case EShootMode::SLOW:					return 20;
		case EShootMode::SPEED:					return 15;
		case EShootMode::STOP:					return 40;
		default:								return 0;
	}
}

FString GetNameOfTheMode(const EShootMode::Type ShootMode)
{
	switch (ShootMode)
	{
		case EShootMode::SLOW:					return FString(TEXT("Slow"));
		case EShootMode::SPEED:					return FString(TEXT("Speed"));
		case EShootMode::STOP:					return FString(TEXT("Stop"));
		default:								return FString(TEXT("Unknown"));
	}

}

FColor GetColorOfTheMode(const EShootMode::Type ShootMode)
{
	switch (ShootMode)
	{
	case EShootMode::SLOW:					return FColor(138, 239, 251);
	case EShootMode::SPEED:					return FColor(0, 255, 0);
	case EShootMode::STOP:					return FColor(255, 255, 255);
	default:								return FColor(0, 0, 0);
	}
}