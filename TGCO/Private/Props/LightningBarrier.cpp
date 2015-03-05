

#include "TGCO.h"
#include "TGCOPlayerController.h"
#include "LightningBarrier.h"
#include "Net/UnrealNetwork.h"


ALightningBarrier::ALightningBarrier(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),
	bIsLightningActive(true)
{
	pBarrier = ObjectInitializer.CreateDefaultSubobject<ULightningBarrierSkeletalMeshComp>(this, TEXT("Barrier"));
	pBarrier->AttachTo(StaticMeshProps);
}

void ALightningBarrier::ChangeActiveState()
{
	if (Role < ROLE_Authority)
	{
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerChangeActiveStateOnBarrier(this, !bIsLightningActive);
		}
	}
	else
	{
		bIsLightningActive = !bIsLightningActive;
		UpdateActiveState();
	}
}

void ALightningBarrier::ChangeActiveStateFromServer(bool bValue)
{
	bIsLightningActive = bValue;
	UpdateActiveState();
}

void ALightningBarrier::OnRep_LightningState()
{
	UpdateActiveState();
}

void ALightningBarrier::UpdateActiveState()
{
	if (pBarrier != nullptr)
	{
		pBarrier->ChangeLightningState(bIsLightningActive);
		if (Role < ROLE_Authority)
		{
			pBarrier->ChangeLightningState(bIsLightningActive);
		}
	}
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

void ALightningBarrier::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(ALightningBarrier, bIsLightningActive);
}