

#include "TGCO.h"
#include "Minesweeper.h"

AMinesweeper::AMinesweeper(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

	//Create all the MinesBox and initialize them without mine
	Squares.AddUninitialized(SIZE);
	for (int i = 0; i < SIZE; ++i)
	{
		Squares[i] = ObjectInitializer.CreateDefaultSubobject<AMinesBox>(this, TEXT("MineBox")) ;
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
			if ( ((i - NB_ROW + j) / NB_COL == (i / NB_COL) - 1) && (Squares[i - NB_ROW + j]->GetIsUndermined() == true) && (i < NB_COL) )
			{
				Squares[i]->SetNeighboursUndermined();
			}
			if (((i + j) / NB_COL == (i / NB_COL)) && (Squares[i + j]->GetIsUndermined() == true) && (j != 0))
			{
				Squares[i]->SetNeighboursUndermined();
			}
			if (((i + NB_ROW + j) / NB_COL == (i / NB_COL) + 1) && (Squares[i + NB_ROW + j]->GetIsUndermined() == true) && (i < SIZE - NB_ROW))
			{
				Squares[i]->SetNeighboursUndermined();
			}
		}
		
	}
}


void AMinesweeper::DeleteMinesweeper()
{
	for (int i = 0; i < SIZE; ++i)
	{
		Squares.RemoveAt(i);
	}
}
