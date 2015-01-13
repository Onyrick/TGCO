

#include "TGCO.h"
#include "Seed.h"


ASeed::ASeed(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SeedShape(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	StaticMesh->SetStaticMesh(SeedShape.Object);
}

bool ASeed::OnInteract()
{
	if (GEngine)
	{
		SeedPicked.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Interactible seed"));
	}
	return true;
}


