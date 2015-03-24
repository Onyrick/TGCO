

#pragma once

#include "GameFramework/Actor.h"
#include <vector>
#include <ctime>
#include "Triggerable/MinesweeperBox.h"
#include "Minesweeper.generated.h"


/**
* @class	AMinesweeper
*
* @brief	The container of minesweeper boxes for the minesweeper puzzle
*/
UCLASS()
class TGCO_API AMinesweeper : public AActor
{
	GENERATED_BODY()

public:

	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	AMinesweeper(const FObjectInitializer& ObjectInitializer);

	/**
	* @brief	Creates the minesweeper.
	*
	*/
	void CreateMinesweeper();

	/**
	* @brief	Gets minesweeper size.
	*		Can be called in BluePrint
	*
	* @return	The minesweeper size.
	*/
	UFUNCTION(BlueprintCallable, Category = "Minesweeper")	
	int32 GetMinesweeperSize();

	/**
	* @brief	Gets  MinesweeperBox at the index position in the Squares Array.
	*		Can be called in BluePrint
	*
	* @param	index	Zero-based index of the Squares Array.
	*
	* @return	null if it fails, else the MinesweeperBox.
	*/
	UFUNCTION(BlueprintCallable, Category = "Minesweeper")
	AMinesweeperBox* GetMinesweeperBoxAt(int32 index);

	/**
	* @brief	Resets all values of the squares of MinesweeperBox. 
	*		Called when the player in the past walk on a mine.
	*		Can be called in BluePrint.
	*/
	UFUNCTION(BlueprintCallable, Category = "Minesweeper")
	void ResetMinesweeper();

	/**
	* @brief	Delete the array that contains AMinesweeperBox.
	*/
	void DeleteMinesweeper();

	/**
	* @brief	Put mines randomly in the TArray of MinesweeperBox.
	*/
	void PutMinesRandomly();

	/**
	* @brief	Calculate the number of neighbours that are undermined.
	*/
	void CalculateNeighboursUndermined();

	/**
	* @brief	Executes the reset console action.
	*		Can be called in BluePrint
	*/
	UFUNCTION(BlueprintCallable, Category = "Minesweeper")
	void OnResetConsole();

	/**
	* @brief	Content all the mine box.
	*/
	TArray<AMinesweeperBox*> Squares;

	/**
	* @brief	Content the BluePrint of the MinesweeperBox.
	*/
	TSubclassOf<class AMinesweeperBox> MinesweeperBoxBP;

private:
	/**
	* @brief	Call ResetMinesweeper on server by client
	*/
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerResetMinesweeper();

	/**
	* @brief The number of columns.
	*/
	const int NB_COL = 5;

	/**
	* @brief	The number of rows.	
	*/
	const int NB_ROW = 5;

	/**
	* @brief	The size of the Minesweeper.
	*/
	const int SIZE = NB_COL * NB_ROW;

	/**
	* @brief	The number of mines presents in minesweeper.
	*/
	const int NB_MINES = 5;

};
