
#include "TGCO.h"
#include "RailType.h"

FString GetNameOfTheRail(const ERailType::Type RailType)
{
	switch (RailType)
	{
	case ERailType::STRAIGHT:					return TEXT("Straight");
	case ERailType::CURVE:						return TEXT("Curve");
	default:									return TEXT("Unknown");
	}

}
