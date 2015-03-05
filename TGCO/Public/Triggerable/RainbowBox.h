

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

	/** Set a color to the RainbowBox */
	void SetColor(const ERainbowBoxColor::Color eNewColor);

	/** Set the color of the RainbowBox */
	ERainbowBoxColor::Color GetColor();

	/** Set bNewShouldNotify to know if the RainbowBox is in the past or in the futur */
	void SetShouldNotify(bool bNewShouldNotify);

	/** Set bNewIsHideInPast to known if the RainbowBox is hidden by the player in the past */
	void SetIsHideInPast(bool bNewIsHideInPast);

	/** Get bNewIsHideInPast */
	bool GetIsHideInPast();
	
private:
	/** The color of the RainbowBox */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_Material)
	int32 iColor;

	/** The material instance */
	UPROPERTY(Transient, Replicated)
	UMaterialInstanceDynamic* MaterialInstanceDynamic;

	/** To know if the RainbowBox is in the past or in the futur and if it sould notify the other RainbowBoxHandler */
	bool bShouldNotify;
	/** To known if the RainbowBox is hidden by the player in the past */
	bool bIsHideInPast;

	/** Function called when iColor is changed by replication, change the color of the material instance */
	UFUNCTION()
	void OnRep_Material();
};
