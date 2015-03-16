

#pragma once

#include <ctime>
#include "GameFramework/Actor.h"
#include "RainbowBox.h"
#include "RainbowBoxColor.h"
#include "RainbowBoxHandlerFuture.generated.h"

UCLASS()
class TGCO_API ARainbowBoxHandlerFuture : public AActor
{
	GENERATED_BODY()
	
public:
	/** Constructors */
	ARainbowBoxHandlerFuture(const FObjectInitializer& ObjectInitializer);

	/** Create the RainbowBoxHandler */
	UFUNCTION(BlueprintCallable, Category = "Rainbow")
	void CreateRainbowBoxHandler();

	/** Delete the array that contains ARainbowBox */
	void DeleteRainbow();

	/** Hide all rainbow box of the passed color */
	void HideAllOfThisColor(ERainbowBoxColor::Color HideColor);

	/** Hide all rainbow box of the color of the passed box color except those passed*/
	void HideAllExcepted(ARainbowBox* StayRainbowBox);

private:
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerCreateRainbowBoxHandler();

public:
	/** Contain all the rainbow box */
	TArray< ARainbowBox* > Squares;
	TSubclassOf<class ARainbowBox> RainbowBoxBP;

private:
	const int NB_COL = 8;
	const int NB_ROW = 8;
	const int SIZE = NB_COL * NB_ROW;

	ARainbowBox* MustStayRainbowBox;

};
