

#include "TGCO.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Slate.h"
#include "ConsoleMinesweeper.h"


AConsoleMinesweeper::AConsoleMinesweeper(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bReplicates = true;
}

void AConsoleMinesweeper::CreateConsoleMinesweeper()
{
	if (!(Role < ROLE_Authority))
	{
		static ConstructorHelpers::FClassFinder<AMinesweeper> ItemBlueprint(TEXT("/Game/Blueprints/Minesweeper_BP"));
		if (ItemBlueprint.Class != NULL)
		{
			Minesweeper = (UClass*)ItemBlueprint.Class;
		}
	}
	else
	{
		ServerCreateConsoleMinesweeper();
	}
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
	CreateConsoleMinesweeper();
}