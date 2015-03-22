

#pragma once

#include "InteractiveElement.h"
#include "Minesweeper.h"
#include "ConsoleMinesweeper.generated.h"

/**
 * @brief An Interactive Element is an element the player can interact with by pressing "E"
 * 	
 * 	@sa AInteractiveElement
 */
UCLASS()
class TGCO_API AConsoleMinesweeper : public AInteractiveElement
{
	GENERATED_UCLASS_BODY()

public:
	/**
	*@brief	Executes when the Player uses the object
	*
	*@return	true if it succeeds, false if it fails.
	*/
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	virtual bool OnInteract() override;

	/**
	*@brief	Event call when the minesweeper is reset.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ConsoleMinesweeper")
	void ResetMinesweeper();

	/** @brief	The camera console. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ConsoleMinesweeper")
	ACameraActor* CameraConsole;
};
