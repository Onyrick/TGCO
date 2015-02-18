

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
	AMinesweeper(const FObjectInitializer& ObjectInitializer);

	/** Create the Minesweeper */
	void CreateMinesweeper();

	/** Get the size of the minesweeper */
	UFUNCTION(BlueprintCallable, Category = "Minesweeper")
		int32 GetMinesweeperSize();

	/** Get the MineBox at the index position in the Squares Array */
	UFUNCTION(BlueprintCallable, Category = "Minesweeper")
		AMinesBox* GetMineBoxAt(int32 index);

	/** Reset all values of the array of MinesweeperBox. Called when the player in the past walk on a mine. */
	UFUNCTION(BlueprintCallable, Category = "Minesweeper")
		void ResetMinesweeper();

	/** Delete the array that contains AMinesBox */
	void DeleteMinesweeper();

	/** Put mines randomly in the TArray of MineBox */
	void PutMinesRandomly();
	/** Calculate the number of neighbours that are undermined */
	void CalculateNeighboursUndermined();

	/** Content all the mine box */
	TArray<AMinesBox*> Squares;
	TSubclassOf<class AMinesBox> MineBoxBP;

private:
	const int NB_COL = 5;
	const int NB_ROW = 5;
	const int SIZE = NB_COL * NB_ROW;
	const int NB_MINES = 4;

};
