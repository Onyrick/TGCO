

#include "TGCO.h"
#include "MinesBox.h"


AMinesBox::AMinesBox(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, bIsUndermined(false)
, iNeighboursUndermined(0)
, bIsDisplayed(false)
{}

void AMinesBox::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogDebug, Warning, TEXT("Begin Overlap MineBox"));
	if (bIsUndermined)
	{
		Explode();
	}
}

void AMinesBox::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogDebug, Warning, TEXT("End Overlap MineBox"));
}

void AMinesBox::SetIsUndermined()
{
	bIsUndermined = !(bIsUndermined);
}

bool AMinesBox::GetIsUndermined()
{
	return bIsUndermined;
}

void AMinesBox::Explode()
{
	UE_LOG(LogDebug, Warning, TEXT("BOOM !!!"));
}

void AMinesBox::SetNeighboursUndermined()
{
	iNeighboursUndermined += 1;
}

unsigned int AMinesBox::GetNeighboursUndermined()
{
	return iNeighboursUndermined;
}