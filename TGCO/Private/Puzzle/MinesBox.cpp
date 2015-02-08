

#include "TGCO.h"
#include "MinesBox.h"


AMinesBox::AMinesBox(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer),
bIsUndermined(false),
iNeighboursUndermined(0)
{
	StaticMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh_MinesBox"));
	RootComponent = StaticMesh;
}

void AMinesBox::SetIsUndermined()
{
	bIsUndermined = !(bIsUndermined);
}

bool AMinesBox::GetIsUndermined()
{
	return bIsUndermined;
}

void AMinesBox::SetNeighboursUndermined()
{
	iNeighboursUndermined += 1;
}

unsigned int AMinesBox::GetNeighboursUndermined()
{
	return iNeighboursUndermined;
}