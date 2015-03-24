
#pragma once

#include "UMG.h"
#include "Blueprint/UserWidget.h"
#include "ConsoleMinesweeperUMG.generated.h"

/**
* TODO
*/
UCLASS()
class TGCO_API UConsoleMinesweeperUMG : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	UConsoleMinesweeperUMG(const FObjectInitializer& ObjectInitializer);
};