
#include "TGCO.h"
#include "ConsoleTuto.h"

AConsoleTuto::AConsoleTuto(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{}

bool AConsoleTuto::IsUnlocked()
{
	return bIsUnlocked;
}

void AConsoleTuto::SetUnlocked(bool _unlock)
{
	bIsUnlocked = _unlock;
}

bool AConsoleTuto::OnInteract()
{
	//TODO
	UE_LOG(LogTest, Warning, TEXT("Console activate"));
	return true;
}
