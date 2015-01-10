

#include "TGCO.h"
#include "FlowerPot.h"



AFlowerPot::AFlowerPot(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	bIsInteractive = false;
}

bool AFlowerPot::OnInteract()
{
	//TODO
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Interactible flower pot"));
	}
	return true;
}


