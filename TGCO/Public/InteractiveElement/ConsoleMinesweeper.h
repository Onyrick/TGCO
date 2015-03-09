

#pragma once

#include "InteractiveElement.h"
#include "Minesweeper.h"
#include "ConsoleMinesweeperUMG.h"
#include "ConsoleMinesweeper.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API AConsoleMinesweeper : public AInteractiveElement
{
	GENERATED_UCLASS_BODY()

public:
	/** Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	virtual bool OnInteract() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ConsoleMinesweeper")
		void ResetMinesweeper();

private:
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerActivateConsoleMinesweeper();
};
