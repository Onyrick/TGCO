

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
	UFUNCTION(BlueprintCallable, Category = "ConsoleMinesweeper")
		void CreateConsoleMinesweeper();

	/** Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	virtual bool OnInteract() override;

	/** The minesweeper the console will manage */
	UPROPERTY(EditAnywhere, Transient, Replicated, Category = "ConsoleMinesweeper")
		TSubclassOf<class AMinesweeper> Minesweeper;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ConsoleMinesweeper")
		UConsoleMinesweeperUMG* Console;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ConsoleMinesweeper")
		void ResetMinesweeper();

private:
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerCreateConsoleMinesweeper();

	
};
