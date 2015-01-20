// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Triggerable/Triggerable.h"
#include "Checkpoint.generated.h"

/**
*
*/
UCLASS()
class TGCO_API ACheckpoint : public ATriggerable
{
	GENERATED_UCLASS_BODY()

public:
	/** Event launch when Player begin to trigger the TriggerBox component. */
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	/** Event launch when Player end to trigger the TriggerBox component. */
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};
