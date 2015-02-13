

#pragma once

#include "GameFramework/Actor.h"
#include <vector>
#include <ctime>
#include "Triggerable/MinesBox.h"
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

	/** Create the Minesweeper */
	UFUNCTION(BlueprintCallable, Category = "Minesweeper")
	void CreateMinesweeper();

	/** Delete the array that contains AMinesBox */
	void DeleteMinesweeper();

	void CalculateNeighboursUndermined();

	/** Content all the mine box */
	TArray< AMinesBox* > Squares;
	TSubclassOf<class AMinesBox> MineBoxBP;

private:
	const int NB_COL = 5;
	const int NB_ROW = 5;
	const int SIZE = NB_COL * NB_ROW;
	const int NB_MINES = 4;

};
