

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
	int* SubmitAnswer(ESolutionType::Type* Answer);

	/** Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "Mastermind")
	virtual bool OnInteract() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diode")
	class UStaticMeshComponent* Diode4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MastermindCamera")
	ACameraActor* CameraPuzzle;

private:
	ESolutionType::Type* Solution;
	void UpdateDiode();
	void SwitchDiodeOn();
	void SwitchDiodeOff();

	UMaterialInstanceDynamic *MaterialInstance1;
	UMaterialInstanceDynamic *MaterialInstance2;
	UMaterialInstanceDynamic *MaterialInstance3;
	UMaterialInstanceDynamic *MaterialInstance4;
	bool bInGame;
};
