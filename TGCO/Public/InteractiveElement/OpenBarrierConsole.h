

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
	* @brief	Check the given code.
	* the code is compared to OpeningCode and if it matches return true, false otherwise
	*
	* @param	code	int32
	*
	* @return	true if it matches OpeningCode false otherwise
	*/
	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		virtual bool CheckCode(int32 code);

	/**
	* @brief	Set OpeningCode.
	*	set the attribute OpeningCode to code value
	* @param	code	int32
	*
	* @return	void
	*/
	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		void SetOpeningCode(int32 code);

	/**
	* @brief	Set OpeningCode.
	*	set the attribute OpeningCode to code value sent by the server
	* @param	code	int32
	*
	* @return	void
	*/
	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		void SetOpeningCodeFromServer(int32 code);

	/** Camera of the puzzle for auto move */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenBarrier")
		ACameraActor* CameraPuzzle;

	/** Array containing pointers to all the barrier it controls */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenBarrier")
		TArray<ALightningBarrier *> ControledTerminals;

	/** Pointer to the displayer that will show the opening code to the future player*/
	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "OpenBarrier")
		ACodeBarrierDisplayer* Displayer;

	/** The opening code that will deactivate all the barriers contained in the ControledTerminals array */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "OpenBarrier")
		int32 OpeningCode;

private:
	/**
	* @brief	Set OpeningCode.
	*	set the attribute OpeningCode to code value sent by the server
	* @param	code	int32
	*
	* @return	void
	*/
	void SetCode(int32 code);

};
