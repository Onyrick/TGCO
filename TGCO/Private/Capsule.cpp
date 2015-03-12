

#include "TGCO.h"
#include "Capsule.h"

ACapsule::ACapsule(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}
TEnumAsByte<ESolutionType::Type> ACapsule::GetSolutionType()
{
	return SolutionType;
}

void ACapsule::IsCurrentlyUsed(bool bNewIsCurrentlyUsed)
{
	bIsCurrentlyUsed = bNewIsCurrentlyUsed;
}


