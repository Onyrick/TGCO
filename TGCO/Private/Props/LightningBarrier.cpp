

#include "TGCO.h"
#include "LightningBarrier.h"


ALightningBarrier::ALightningBarrier(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),
	bIsLightningActive(true)
{
	pBarrier = ObjectInitializer.CreateDefaultSubobject<ULightningBarrierSkeletalMeshComp>(this, TEXT("Barrier"));
	pBarrier->AttachTo(StaticMeshProps);
}

void ALightningBarrier::ChangeActiveState()
{
	bIsLightningActive = !bIsLightningActive;
	pBarrier->ChangeLightningState(bIsLightningActive);
}

void ALightningBarrier::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if ((PropertyName == GET_MEMBER_NAME_CHECKED(ALightningBarrier, bIsLightningActive)) && pBarrier != nullptr)
	{
		pBarrier->ChangeLightningState(bIsLightningActive);
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
