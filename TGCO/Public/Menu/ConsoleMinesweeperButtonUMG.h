
#pragma once

#include "UMG.h"
#include "Blueprint/UserWidget.h"
#include "ConsoleMinesweeperButtonUMG.generated.h"

/**
* TODO
*/
UCLASS()
class TGCO_API UConsoleMinesweeperButtonUMG : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	UConsoleMinesweeperButtonUMG(const FObjectInitializer& ObjectInitializer);
};