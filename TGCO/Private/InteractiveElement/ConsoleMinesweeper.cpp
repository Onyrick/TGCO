

#include "TGCO.h"
#include "ConsoleMinesweeper.h"


AConsoleMinesweeper::AConsoleMinesweeper(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<AMinesweeper> ItemBlueprint(TEXT("/Game/Blueprints/Minesweeper_BP"));
	if (ItemBlueprint.Class != NULL)
	{
		Minesweeper = (UClass*)ItemBlueprint.Class;
	}
	bReplicates = true;
}

bool AConsoleMinesweeper::OnInteract()
{
	UE_LOG(LogTest, Warning, TEXT("Console activate"));
	return true;
}

void AConsoleMinesweeper::ResetMinesweeper_Implementation()
{
}

bool AConsoleMinesweeper::ServerCreateConsoleMinesweeper_Validate()
{
	return true;
}

void AConsoleMinesweeper::ServerCreateConsoleMinesweeper_Implementation()
{
	
}