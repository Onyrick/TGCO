
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
	/** Constructors */
	UConsoleMinesweeperUMG(const FObjectInitializer& ObjectInitializer);

	/** Create Console Minesweeper UMG with authority */
	UFUNCTION(BlueprintCallable, Category = "ConsoleMinesweeperUMG")
	void CreateConsoleMinesweeperUMG();

private:
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerCreateConsoleMinesweeperUMG();
};