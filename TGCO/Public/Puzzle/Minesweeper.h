

#pragma once

#include "GameFramework/Actor.h"
#include <vector>
#include <ctime>
#include "Puzzle/MinesBox.h"
#include "Minesweeper.generated.h"


/**
 * 
 */
UCLASS()
class TGCO_API AMinesweeper : public AActor
{
	GENERATED_BODY()

public:
	AMinesweeper(const FObjectInitializer& PCIP);
	void DeleteMinesweeper();

	void CalculateNeighboursUndermined();

	const int NB_COL = 10;
	const int NB_ROW = 10;
	const int SIZE = NB_COL * NB_ROW;
	const int NB_MINES = 9;
	TArray< AMinesBox* > Squares;

};
