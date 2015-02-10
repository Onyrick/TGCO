

#include "TGCO.h"
#include "Minesweeper.h"

AMinesweeper::AMinesweeper(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//Create all the MinesBox and initialize them without mine
	for (int i = 0; i < SIZE; ++i)
	{
		Squares.Add(ObjectInitializer.CreateDefaultSubobject<AMinesBox>(this, FName(TEXT("MineBox%d"),i )));
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
	UE_LOG(LogDebug, Warning, TEXT("####### END ########"));
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
		
	}
}


void AMinesweeper::DeleteMinesweeper()
{
	Squares.Empty();
}
