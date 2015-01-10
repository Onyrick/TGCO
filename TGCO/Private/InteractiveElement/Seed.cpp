

#include "TGCO.h"
#include "Seed.h"


ASeed::ASeed(const class FObjectInitializer& PCIP) : Super(PCIP)
{

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


