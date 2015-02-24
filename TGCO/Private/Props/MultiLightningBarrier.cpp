
#include "TGCO.h"
#include <Props/LightningBarrier.h>
#include "MultiLightningBarrier.h"
#include <string>


AMultiLightningBarrier::AMultiLightningBarrier(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),
	iNbBarriers(1)
{
	m_vBarriers.Push(this);
}

void AMultiLightningBarrier::ReceiveDestroyed()
{
	while (m_vBarriers.Num() > 1)
	{
		/**
		 *	Remove all elements of the array and delete them
		 * (normal destructor just empty the array leaving all elements
		 * the world)
		 */
		auto barrier = m_vBarriers.Pop(true);
		if (barrier != nullptr)
		{
			barrier->Destroy();
		}
	}

	Super::ReceiveDestroyed();
}

void AMultiLightningBarrier::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	/* Check if the property change event is applied to the array*/
	if ((PropertyName == GET_MEMBER_NAME_CHECKED(AMultiLightningBarrier, m_vBarriers)))
	{
		/*if the array is emptied push back this as the first element*/
		if (PropertyChangedEvent.ChangeType == EPropertyChangeType::ValueSet)
		{
			if (m_vBarriers.Num() == 0)
			{
				m_vBarriers.Push(this);
				iNbBarriers = 1;
			}
		}
	}
	/* Check if the property change event is applied to the number of barrier */
	if ((PropertyName == GET_MEMBER_NAME_CHECKED(AMultiLightningBarrier, iNbBarriers)))
	{
		int num = m_vBarriers.Num();
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
					prevBar = m_vBarriers.Last();
					if (prevBar == nullptr)
					{
						prevBar = (ALightningBarrier*)this;
					}
					FVector SpawnLocation = FVector(0);
					FVector Origin, BoxExtent;
					prevBar->GetActorBounds(false, Origin, BoxExtent);
					SpawnLocation.Z = Origin.Z + BoxExtent.Z - loc.Z;
					auto barrier = World->SpawnActor<ALightningBarrier>(ALightningBarrier::StaticClass(), SpawnLocation, SpawnRotation);
					if (m_vBarriers.Num() == 1)
					{
						barrier->GetActorBounds(false, Origin, BoxExtent);
						barrier->SetActorRelativeTransform(FTransform(FRotator::ZeroRotator, FVector(0.f, 0.f, Origin.Z + BoxExtent.Z), FVector(1.0)));
					}
					barrier->getStaticMesh()->SetMobility(EComponentMobility::Stationary);
					barrier->getStaticMesh()->AttachTo(StaticMeshProps);
					barrier->GetRootComponent()->SetAbsolute(false, false, true);
					m_vBarriers.Push(barrier);
				}
			}
		}
		/*if user has decreased the number of barrier*/
		else
		{
			for (int i = 0; i < num - iNbBarriers; i++)
			{
				auto barrier = m_vBarriers.Pop(true);
				barrier->Destroy();
			}
		}
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

