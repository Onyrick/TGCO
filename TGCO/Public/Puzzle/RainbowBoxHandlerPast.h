

#pragma once

#include <ctime>
#include "GameFramework/Actor.h"
#include "RainbowBox.h"
#include "RainbowBoxHandlerPast.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API ARainbowBoxHandlerPast : public AActor
{
	GENERATED_BODY()

public:
	ARainbowBoxHandlerPast(const FObjectInitializer& PCIP);

	/** Create the RainbowBoxHandler */
	UFUNCTION(BlueprintCallable, Category = "Rainbow")
	void CreateRainbowBoxHandler();

	/** Delete the array that contains ARainbowBox */
	void DeleteRainbow();

	/** Content all the rainbow box */
	TArray< ARainbowBox* > Squares;
	TSubclassOf<class ARainbowBox> RainbowBoxBP;

private:
	const int NB_COL = 5;
	const int NB_ROW = 5;
	const int SIZE = NB_COL * NB_ROW;
	
};
