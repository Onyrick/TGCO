

#pragma once

#include <ctime>
#include "GameFramework/Actor.h"
#include "RainbowBox.h"
#include "RainbowBoxColor.h"
#include "RainbowBoxHandlerFutur.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API ARainbowBoxHandlerFutur : public AActor
{
	GENERATED_BODY()
	
public:
	ARainbowBoxHandlerFutur(const FObjectInitializer& PCIP);

	/** Create the RainbowBoxHandler */
	UFUNCTION(BlueprintCallable, Category = "Rainbow")
	void CreateRainbowBoxHandler();

	/** Delete the array that contains ARainbowBox */
	void DeleteRainbow();

	/** Hide all rainbow box except those of the passed color */
	void HideAllExcepted(ERainbowBoxColor::Color StayColor);

	/** Content all the rainbow box */
	TArray< ARainbowBox* > Squares;
	TSubclassOf<class ARainbowBox> RainbowBoxBP;

private:
	const int NB_COL = 5;
	const int NB_ROW = 5;
	const int SIZE = NB_COL * NB_ROW;
};
