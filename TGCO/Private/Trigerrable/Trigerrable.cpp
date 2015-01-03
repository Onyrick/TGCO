#include "TGCO.h"
#include "Trigerrable.h"

UTrigerrable::UTrigerrable(const class FObjectInitializer& PCIP) : Super(PCIP)
{

}

void ITrigerrable::OnComponentBeginOverlap()
{
	unimplemented();
}

void ITrigerrable::OnComponentEndOverlap()
{
	unimplemented();
}