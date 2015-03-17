

#pragma once

#include "Triggerable.h"
#include "MinesBox.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API AMinesBox : public ATriggerable
{
	GENERATED_BODY()
	
public:
	AMinesBox(const FObjectInitializer& ObjectInitializer);

	/** Event launch when Player begin to trigger the TriggerBox component. */
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	/** Event launch when Player end to trigger the TriggerBox component. */
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	/** Getter and Setter of the variable bIsUndermined */
	void SetIsUndermined();
	bool GetIsUndermined();

	/** Getter and Setter of the variable iNeigbourgsUndermined */
	void SetNeighboursUndermined();
	unsigned int GetNeighboursUndermined();
	/** Launch an explosion animation. Reinit the DeminorPuzzle. Do some damage to the Player. Eject the Player to the Checkpoint of the Level */
	void Explode(class AActor* OtherActor);

	/** Reinit the information displayed by the past. Set bInfoPast to false. */
	void ReinitDisplayInformation();

	/** Set the value to know if there is something to draw on the AMinesweeperBox : true : flag, flase : no flag  */
	UFUNCTION(BlueprintCallable, Category = "MineBox")
	void SetIsMarked();

	/** Get the value to know if the flag is visible in MineBox */
	UFUNCTION(BlueprintCallable, Category = "MineBox")
	bool IsMarked();

	/** Set the visibility of the flag */
	UFUNCTION(BlueprintCallable, Category = "MineBox")
	void SetVisibilityOfFlag();

	/** The Text Render representing the number of Neighbours which are undermined */
	UPROPERTY(VisibleAnywhere, Transient, Replicated, BlueprintReadWrite, Category = Text)
		UTextRenderComponent* Number;

	/** The Mesh representing a flag. Will be visible thanks to the console */
	UPROPERTY(EditAnywhere, Transient, Replicated, Category = Meshes)
		UStaticMeshComponent* MineFlag;

protected:
	/** Wheteher a mineBox is undermined */
	UPROPERTY(Transient, Replicated)
	bool bIsUndermined;

	/** Know if there is something to draw on the AMinesweeperBox : true : flag, flase : no flag */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_Flag)
	bool bIsMarked;

	/** The number of neighbourgs which are undermined. */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_TextRender)
	int32 iNeighboursUndermined;

	/** Whether the number is displayed */
	bool bIsDisplayed;

	UFUNCTION()
	void OnRep_TextRender();

	UFUNCTION()
	void OnRep_Flag();
};
