
#include "TGCO.h"
#include <Props/LightningBarrier.h>
#include "MultiLightningBarrier.h"
#include <string>
#include "Net/UnrealNetwork.h"


AMultiLightningBarrier::AMultiLightningBarrier(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),
	iNbBarriers(1)
{
	aBarriers.Push(this);
}

void AMultiLightningBarrier::ReceiveDestroyed()
{
	while (aBarriers.Num() > 1)
	{
		/**
		 *	Remove all elements of the array and delete them
		 * (normal destructor just empty the array leaving all elements
		 * the world)
		 */
		auto barrier = aBarriers.Pop(true);
		if (barrier != nullptr)
		{
			barrier->Destroy();
		}
	}

	Super::ReceiveDestroyed();
}

void AMultiLightningBarrier::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	/* Check if the property change event is applied to the array*/
	if ((PropertyName == GET_MEMBER_NAME_CHECKED(AMultiLightningBarrier, aBarriers)))
	{
		/*if the array is emptied push back this as the first element*/
		if (PropertyChangedEvent.ChangeType == EPropertyChangeType::ValueSet)
		{
			if (aBarriers.Num() == 0)
			{
				aBarriers.Push(this);
				iNbBarriers = 1;
			}
		}
	}
	/* Check if the property change event is applied to the number of barrier */
	if ((PropertyName == GET_MEMBER_NAME_CHECKED(AMultiLightningBarrier, iNbBarriers)))
	{
		int num = aBarriers.Num();
		if (iNbBarriers < 1)
		{
			iNbBarriers = 1;
		}
		/*if user has increased the number of barrier*/
		if (iNbBarriers > num)
		{
			const FRotator SpawnRotation = FRotator::ZeroRotator;
			auto loc = this->GetActorLocation();

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				for (int i = 0; i < iNbBarriers - num; i++)
				{
					AActor * prevBar = nullptr;
					prevBar = aBarriers.Last();
					if (prevBar == nullptr)
					{
						prevBar = (ALightningBarrier*)this;
					}
					FVector SpawnLocation = FVector(0);
					FVector Origin, BoxExtent;
					prevBar->GetActorBounds(false, Origin, BoxExtent);
					SpawnLocation.Z = Origin.Z + BoxExtent.Z - loc.Z;
					auto barrier = World->SpawnActor<ALightningBarrier>(ALightningBarrier::StaticClass(), SpawnLocation, SpawnRotation);
					if (aBarriers.Num() == 1)
					{
						barrier->GetActorBounds(false, Origin, BoxExtent);
						barrier->SetActorRelativeTransform(FTransform(FRotator::ZeroRotator, FVector(0.f, 0.f, Origin.Z + BoxExtent.Z), FVector(1.0)));
					}
					barrier->GetStaticMesh()->SetMobility(EComponentMobility::Stationary);
					barrier->GetStaticMesh()->AttachTo(StaticMeshProps);
					barrier->GetRootComponent()->SetAbsolute(false, false, true);
					aBarriers.Push(barrier);
				}
			}
		}
		/*if user has decreased the number of barrier*/
		else
		{
			for (int i = 0; i < num - iNbBarriers; i++)
			{
				auto barrier = aBarriers.Pop(true);
				barrier->Destroy();
			}
		}
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}


void AMultiLightningBarrier::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AMultiLightningBarrier, aBarriers);
	DOREPLIFETIME(AMultiLightningBarrier, iNbBarriers);	
}
