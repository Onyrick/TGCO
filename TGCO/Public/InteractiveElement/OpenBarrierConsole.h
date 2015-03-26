

#pragma once

#include "Props/Props.h"
#include "InteractiveElement/InteractiveElement.h"
#include "InteractiveElement/CodeBarrierDisplayer.h"
#include "Props/LightningBarrier.h"
#include "OpenBarrierConsole.generated.h"

/**
 *
 */
UCLASS()
class TGCO_API AOpenBarrierConsole : public AInteractiveElement
{
	GENERATED_BODY()

public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	AOpenBarrierConsole(const FObjectInitializer& ObjectInitializer);

	/**
	* @brief	Enter or leave the puzzle, move camera and set correct inputs.
	*/
	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		virtual bool OnInteract() override;

	/**
	* @brief	
	*/
	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		virtual bool CheckCode(int32 code);

	/**
	* @brief
	*/
	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		void SetOpeningCode(int32 code);

	/**
	* @brief
	*/
	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		void SetOpeningCodeFromServer(int32 code);

	/** Camera of the puzzle for auto move */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenBarrier")
		ACameraActor* CameraPuzzle;

	/** Array containing pointers to all the barrier it controls */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenBarrier")
		TArray<ALightningBarrier *> ControledTerminals;

	/** Array containing pointers to all the barrier it controls */
	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "OpenBarrier")
		ACodeBarrierDisplayer* Displayer;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "OpenBarrier")
		int32 OpeningCode;

private:
	void SetCode(int32 code);

};
