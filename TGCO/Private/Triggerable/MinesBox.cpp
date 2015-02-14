

#include "TGCO.h"
#include "MinesBox.h"


AMinesBox::AMinesBox(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, bIsUndermined(false)
, iNeighboursUndermined(0)
, bIsDisplayed(false)
{
	Number = ObjectInitializer.CreateDefaultSubobject<UTextRenderComponent>(this, TEXT("Number_MineBox"), true );
	Number->SetRelativeRotation(FRotator(90.0, 90.0, 0.0));
	Number->SetRelativeLocation(FVector(0.0,0.0,25.0));
	Number->SetText(TEXT("0"));
	Number->SetWorldSize(150.0);
	Number->SetVisibility(false);
	Number->AttachParent = RootComponent;
}

void AMinesBox::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsUndermined)
	{
		Explode();
	}
	else
	{
		if (Number != NULL)
		{
			Number->SetVisibility(true);
		}	
	}
}

void AMinesBox::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Number != NULL)
	{
		Number->SetVisibility(false);
	}
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