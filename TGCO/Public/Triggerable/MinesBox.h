

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

	/** The Text Render representing the number of Neighbours which are undermined */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Text)
		UTextRenderComponent* Number;

protected:
	/** Wheteher a mineBox is undermined */
	bool bIsUndermined;

	/** The number of neighbourgs which are undermined. This number will be written on the box */
	unsigned int iNeighboursUndermined;

	/** Whether the number is displayed */
	bool bIsDisplayed;
	
	/** Know if there is something to draw on the AMinesweeperBox : true : flag, flase : no flag */
	bool bInfoPast;
};
