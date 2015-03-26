

#include "TGCO.h"
#include "BarrierColor.h"


FColor GetBarrierColor(const EBarrierColor BarrierColor)
{
	switch (BarrierColor)
	{
	case EBarrierColor::VE_Blue:		return FColor(12, 12, 255);
	case EBarrierColor::VE_Green:		return FColor(12, 255, 12);
	case EBarrierColor::VE_Orange:		return FColor(226, 230, 93);
	case EBarrierColor::VE_Yellow:		return FColor(12, 230, 230);
	case EBarrierColor::VE_Red:			return FColor(255, 12, 12);
	case EBarrierColor::VE_Purple:		return FColor(230, 12, 230);
	default:							return FColor(0, 0, 0);
	}
}

