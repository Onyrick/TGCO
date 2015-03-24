

#include "TGCO.h"
#include "Capsule.h"

ACapsule::ACapsule(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{}

TEnumAsByte<ESolutionType::Type> ACapsule::GetSolutionType()
{
	return SolutionType;
}

void ACapsule::UpdateIsCurrentlyUsed(bool bNewIsCurrentlyUsed)
{
	bIsCurrentlyUsed = bNewIsCurrentlyUsed;
}

bool ACapsule::IsCurrentlyUsed()
{
	return bIsCurrentlyUsed;
}
