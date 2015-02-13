

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
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = -1 ; j <= 1 ; ++j)
		{
			if (((i - NB_ROW + j) / NB_COL == (i / NB_COL) - 1) && (i - NB_ROW + j > 0) && (i < NB_COL))
			{
				if (Squares[i - NB_ROW + j]->GetIsUndermined() == true)
				{
					Squares[i]->SetNeighboursUndermined();
				}
				
			}
			if (((i + j) / NB_COL == (i / NB_COL)) && (i + j > 0) && (j != 0))
			{
				if (Squares[i + j]->GetIsUndermined() == true)
				{
					Squares[i]->SetNeighboursUndermined();
				}
				
			}
			if (((i + NB_ROW + j) / NB_COL == (i / NB_COL) + 1) && (i + NB_ROW + j > 0) && (i < SIZE - NB_ROW))
			{
				if (Squares[i + NB_ROW + j]->GetIsUndermined() == true)
				{
					Squares[i]->SetNeighboursUndermined();
				}
				
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
