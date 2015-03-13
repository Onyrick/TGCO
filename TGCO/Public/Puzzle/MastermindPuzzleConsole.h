

#pragma once

#include "InteractiveElement/InteractiveElement.h"
#include "SolutionType.h"
#include "MastermindPuzzleConsole.generated.h"


UCLASS()
class TGCO_API AMastermindPuzzleConsole : public AInteractiveElement
{
	GENERATED_BODY()
	
public:
	AMastermindPuzzleConsole(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	void SubmitAnswer();

	/** Initialize Mastermind solution */
	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	virtual bool OnInteract() override;

	/** Diode components */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode4;

	/** Camera of the puzzle for auto move */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MastermindCamera")
	ACameraActor* CameraPuzzle;

	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	void SetProposalAt(ESolutionType::Type NewProposal, int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	void RemoveProposalAt(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	ESolutionType::Type GetProposalAt(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	void ClearProposal();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Mastermind")
	void QuitMastermindPuzzleConsole();

private:
	/** Solution of the mastermind */
	ESolutionType::Type* Solution;
	ESolutionType::Type* Proposal;
	void UpdateDiode(int* Difference);

	/** Update color of the diodes according the proposition of the player
	* TO DO
	*/
	void UpdateDiode();
	/** Switch all light on */
	void SwitchDiodeOn();
	/** Switch all light off */
	void SwitchDiodeOff();

	/** Materials of the diode */
	UMaterialInstanceDynamic *MaterialInstance1;
	UMaterialInstanceDynamic *MaterialInstance2;
	UMaterialInstanceDynamic *MaterialInstance3;
	UMaterialInstanceDynamic *MaterialInstance4;
	/** Boolean to know if the player is in game or in puzzle */
	bool bInGame;
};
