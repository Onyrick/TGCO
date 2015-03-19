
#pragma once

#include <ctime>
#include "GameFramework/Actor.h"
#include "RainbowBox.h"
#include "RainbowBoxHandlerPast.generated.h"

/**
* @class	ARainbowBoxHandlerPast
*
* @brief	The container of rainbow boxes for the rainbow puzzle in the past
*
* It is the container of rainbow boxes for the rainbow puzzle in the past.
*
*/
UCLASS()
class TGCO_API ARainbowBoxHandlerPast : public AActor
{
	GENERATED_BODY()

public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	ARainbowBoxHandlerPast(const FObjectInitializer& ObjectInitializer);

	/**
	* @brief	Create rainbow boxes, store and spawn them.
	*/
	UFUNCTION(BlueprintCallable, Category = "Rainbow")
	void CreateRainbowBoxHandler();

	/**
	* @brief	Empty the array that contains ARainbowBox.
	*/
	void DeleteRainbow();

	/**
	* @brief	Hide all rainbow box of the color of the passed box color except those passed.
	*/
	void HideAllExcepted(ARainbowBox* StayRainbowBox);


private:

	/**
	* @brief	Server call to CreateRainbowBoxHandler().
	*/
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerCreateRainbowBoxHandler();

public: 
	/** Contain all the rainbow box */
	TArray< ARainbowBox* > Handler;
	/** The blueprint of RainbowBox*/
	TSubclassOf<class ARainbowBox> RainbowBoxBP;

	/** Number of columns */
	UPROPERTY(EditAnywhere, Category = "RaibowBox handler")
	int32 iColumns;

	/** Number of rows */
	UPROPERTY(EditAnywhere, Category = "RaibowBox handler")
	int32 iRows;

private:
	/** Size of the puzzle */
	int iSize;
};
