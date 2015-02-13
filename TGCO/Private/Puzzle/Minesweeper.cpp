

#include "TGCO.h"
#include "Minesweeper.h"

AMinesweeper::AMinesweeper(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/MinesBox_BP'"));
	//if (ItemBlueprint.Object){
	static ConstructorHelpers::FClassFinder<AMinesBox> ItemBlueprint(TEXT("/Game/Blueprints/MineBox_BP"));
	if (ItemBlueprint.Class != NULL)
	{
		MineBoxBP = (UClass*)ItemBlueprint.Class;
	}
}

void AMinesweeper::CreateMinesweeper()
{
	//Create all the MinesBox and initialize them without mine
	for (int i = 0; i < SIZE; ++i)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			unsigned int x = i / NB_COL;
			unsigned int y = i % NB_COL;
			const FVector SpawnLocation = GetActorLocation() + FVector(x*405 , y*405, 5.0);
			const FRotator SpawnRotation = GetActorRotation();
			AMinesBox* m = (AMinesBox*)World->SpawnActor<AMinesBox>(MineBoxBP, SpawnLocation, SpawnRotation);
			Squares.Add(m);
		}

		//Squares.Add(ObjectInitializer.CreateDefaultSubobject<AMinesBox>(this, FName(TEXT("MineBox%d"),i )));
	}

	//Random place mine
	int iSecret;
	srand(time(NULL));
	for (int cpt = 0; cpt < NB_MINES; ++cpt)
	{
		iSecret = rand() % SIZE;
		if (Squares[iSecret]->GetIsUndermined() != true)
		{
			Squares[iSecret]->SetIsUndermined();
		}
		else
		{
			--cpt;
		}
	}

	CalculateNeighboursUndermined();
}


void AMinesweeper::CalculateNeighboursUndermined()
{
	//For all MineBox
	for (int i = 0; i < SIZE; ++i)
	{
		//Check the neighbours
		for (int j = -1; j <= 1; ++j)
		{
			// If the MineBox is at the beginning of a row, don't check the previous one. 
			// And if it is at the end of the row, don't check the next one.
			if (((i%NB_COL == 0) && (j == -1)) 
				|| ((i%NB_COL == NB_COL - 1) && (j == 1)) )
			{
				continue;
			}
			// Check the neighbours up
			if ((i/NB_COL > 0) && (Squares[i - NB_COL + j]->GetIsUndermined() == true))
			{
				Squares[i]->SetNeighboursUndermined();
				UE_LOG(LogDebug, Warning, TEXT("%d is undermined"), i);
			}
			// Check the neighbours on the left and on the right
			if ((j != 0) && (Squares[i + j]->GetIsUndermined() == true))
			{
				Squares[i]->SetNeighboursUndermined();
				UE_LOG(LogDebug, Warning, TEXT("%d is undermined"), i);
			}
			// Check the neighbours down
			if ((i / NB_COL < NB_COL-1) && (Squares[i + NB_COL + j]->GetIsUndermined() == true))
			{
				Squares[i]->SetNeighboursUndermined();
				UE_LOG(LogDebug, Warning, TEXT("%d is undermined"), i);
			}
			
		}
		
		if (Squares[i]->Number != NULL)
		{
			Squares[i]->Number->SetText(FString::Printf(TEXT("%d"), Squares[i]->GetNeighboursUndermined()));
		}
		
	}
}


void AMinesweeper::DeleteMinesweeper()
{
	Squares.Empty();
}
