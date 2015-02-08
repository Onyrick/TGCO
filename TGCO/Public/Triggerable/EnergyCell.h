// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Triggerable.h"
#include "EnergyCell.generated.h"

/**
 * TODO 
 */
UCLASS()
class TGCO_API AEnergyCell : public ATriggerable
{
	GENERATED_UCLASS_BODY()

public:
	/** Event launch when Player begin to trigger the TriggerBox component. */
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	/** Event launch when Player end to trigger the TriggerBox component. */
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	/** Getter for iAmountOfEnergy. Useless ? */
	UFUNCTION(BlueprintCallable, Category = "EnergyCell")
	int32 GetAmountOfEnergy();
	
	/** Setter for iAmountOfEnergy */
	UFUNCTION(BlueprintCallable, Category = "EnergyCell")
	void SetAmountOfEnergy(int32 _unlock);

protected:
	/**
	 * Set the AEnergyCell as consumed when the Player hit the OnComponentBeginOverlap.
	 * Hide the AEnergyCell in the Level. Increase Player's energy.
	 */
	void Consumed();

protected:
	/** The amount of energy containing in the cell */
	int32 iAmountOfEnergy;
};
