

#include "TGCO.h"
#include "LightningSwitch.h"


ALightningSwitch::ALightningSwitch(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SwitchShape(TEXT("StaticMesh'/Game/StarterContent/Props/SM_CornerFrame.SM_CornerFrame'"));
	StaticMesh->SetStaticMesh(SwitchShape.Object);
	StaticMesh->SetWorldScale3D(FVector(10.f, 10.f, 10.0f));
}


bool ALightningSwitch::OnInteract()
{
	//TODO
	UE_LOG(LogDebug, Warning, TEXT("Interactible Lightning Switch"));

	for (auto Iter(m_vControledTerminals.CreateIterator()); Iter; Iter++)
	{
		if ((*Iter) != nullptr)
		{
			(*Iter)->ChangeActiveState();
		}
	}

	return true;
}
