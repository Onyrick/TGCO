
#pragma once

#include "InteractiveElement/InteractiveElement.h"
#include "SolutionType.h"
#include "MastermindPuzzleConsole.generated.h"

/**
* @class	AMastermindPuzzleConsole
*
* @brief	The console for the mastermind puzzle
*
* Create the solution of the mastermind, receive proposals from the user, and display clues.
*
* @sa	AInteractiveElement
*/
UCLASS()
class TGCO_API AMastermindPuzzleConsole : public AInteractiveElement
{
	GENERATED_BODY()
	
public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	AMastermindPuzzleConsole(const FObjectInitializer& ObjectInitializer);

	/**
	* @brief	On begin play, create the mastermind.
	*/
	virtual void BeginPlay() override;

	/**
	* @brief	Submit the current proposal of the player and update display.
	*/
	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	void SubmitAnswer();

	/**
	* @brief	Enter or leave the puzzle, move camera and set correct inputs.
	*/
	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	virtual bool OnInteract() override;

	/**
	* @brief	Set the SolutionType proposal at a position.
	*
	* @param	NewProposal	The new proposal.
	* @param	iIndex	   	Index for the new proposal.
	*/
	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	void SetProposalAt(ESolutionType::Type NewProposal, int32 iIndex);

	/**
	* @brief	Remove the SolutionType proposal at this position.
	*
	* @param	iIndex	   	Index where to remove.
	*/
	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	void RemoveProposalAt(int32 iIndex);

	/**
	* @brief	Get the SolutionType proposal at this position.
	*
	* @param	iIndex	   	Index where to get.
	* @return	ESolutionType::Type	   	Index where to get.
	*/
	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	ESolutionType::Type GetProposalAt(int32 iIndex);

	/**
	* @brief	Delete all SolutionType of the proposal.
	*/
	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	void ClearProposal();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Mastermind")
	void QuitMastermindPuzzleConsole();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableEvent_UpdateCameraGameToPuzzle);
	/** Called when need to move the camera */
	UPROPERTY(BlueprintAssignable, Category = "Puzzle")
		FBindableEvent_UpdateCameraGameToPuzzle UpdateCameraGameToPuzzle;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableEvent_UpdateCameraPuzzleToGame);
	/** Called when need to move the camera */
	UPROPERTY(BlueprintAssignable, Category = "Puzzle")
		FBindableEvent_UpdateCameraPuzzleToGame UpdateCameraPuzzleToGame;

private: 
	/**
	* @brief	Create the solution of the mastermind.
	*/
	TArray<int32> CreateRandomArrayOfSolution(int32 iSize);

	void UpdateDiode();

	/**
	* @brief	Update diodes color according the proposition of the player.
	*
	* @param	Difference	   	Index where to get.
	*/
	void UpdateDiode(int* Difference);

	/**
	* @brief	Update diodes color like if their are on.
	*/
	void SwitchDiodeOn();
	/**
	* @brief	Update diodes color like if their are off.
	*/
	void SwitchDiodeOff();

public:
	/** First diode component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode1;
	/** Second diode component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode2;
	/** Third diode component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode3;
	/** Fourth diode component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode4;

	/** Camera of the puzzle for auto move */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MastermindCamera")
	ACameraActor* CameraPuzzle;

private:
	/** Solution of the mastermind */
	ESolutionType::Type* Solution;
	/** Proposal of the user for the mastermind */
	ESolutionType::Type* Proposal;

	/** Array of materials for diodes*/
	TArray<UMaterialInstanceDynamic*> MaterialArray;

};
