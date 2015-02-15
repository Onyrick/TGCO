

#pragma once

#include "RainbowBoxColor.h"
#include "Triggerable/Triggerable.h"
#include "RainbowBox.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API ARainbowBox : public ATriggerable
{
	GENERATED_UCLASS_BODY()
	
public:
	/** Event launch when Player begin to trigger the TriggerBox component. */
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	/** Event launch when Player end to trigger the TriggerBox component. */
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	/** Hide and disable collision */
	void Hide();

	/** Show and enable collision */
	void Show();

	void SetColor(const ERainbowBoxColor::Color eColor);
	ERainbowBoxColor::Color GetColor();
	void SetShouldNotify(bool bNewShouldNotify);
	void SetIsHideInPast(bool bNewIsHideInPast);
	bool GetIsHideInPast();
	
private:
	ERainbowBoxColor::Color Color;
	UMaterialInstanceDynamic* MaterialInstanceDynamic;
	bool bShouldNotify;
	bool bIsHideInPast;
};
