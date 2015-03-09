

#include "TGCO.h"
#include "TGCOPlayerController.h"
#include "ConsoleMinesweeper.h"


AConsoleMinesweeper::AConsoleMinesweeper(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bReplicates = true;
}

bool AConsoleMinesweeper::OnInteract()
{
	return true;
}

void AConsoleMinesweeper::ResetMinesweeper_Implementation()
{
	UE_LOG(LogTest, Warning, TEXT("Je suis dans ResetMinesweeper"));
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains("Minesweeper_Futur") && ActorItr->GetActorClass()->GetDescription() == FString(TEXT("Minesweeper BP")))
		{
			AMinesweeper* Minesweeper = Cast<AMinesweeper>(*ActorItr);
			Minesweeper->GetMineBoxAt(0)->SetVisibilityOfFlag();
		}
	}
}

