
#pragma once

#include "RainbowBoxColor.h"
#include "Triggerable/Triggerable.h"
#include "RainbowBox.generated.h"

/**
* @class	ARainbowBox
*
* @brief	Rainbow boxes for the rainbow box puzzle
*
*/
UCLASS()
class TGCO_API ARainbowBox : public ATriggerable
{
	GENERATED_UCLASS_BODY()
	
public:

	/**
	 * @brief	When player walk on a rainbow box.
	 *
	 * @param	OtherActor	If non-null, the other actor.
	 * @param	OtherComp 	If non-null, the other component.
	 * @param	OtherBodyIndex	  	Zero-based index of the other body.
	 * @param	bFromSweep		  	true to from sweep.
	 * @param	SweepResult		  	The sweep result.
	 *
	 * ### summary	Event launch when Player begin to trigger the TriggerBox component.
	 */
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	/**
	 * @brief	Executes the overlap end action.
	 *
	 * @param	OtherActor	If non-null, the other actor.
	 * @param	OtherComp 	If non-null, the other component.
	 * @param	OtherBodyIndex	  	Zero-based index of the other body.
	 *
	 * ### summary	Event launch when Player end to trigger the TriggerBox component.
	 */
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	/** 
	 * @brief Hide and disable collision 
	*/
	void Hide();

	/** 
	 * @brief Show and enable collision
	*/
	void Show();

	/** 
	 * @brief Set a color to the RainbowBox
	 * 
	 * @param eNewColor The color to be set
	*/
	void SetColor(const ERainbowBoxColor::Color eNewColor);

	/** 
	 * @brief Get the color of the RainbowBox
	 * 
	 * @return ERainbowBoxColor::Color The color of the RainbowBox
	*/
	ERainbowBoxColor::Color GetColor();

	/** 
	 * @brief Set bNewShouldNotify to know if the RainbowBox is in the past or in the futur
	*/
	void SetShouldNotify(bool bNewShouldNotify);

	/** 
	 * @brief Set bNewIsHideInPast to known if the RainbowBox is hidden by the player in the past (and had to be hidden inthe futur)
	*/
	void SetIsHideInPast(bool bNewIsHideInPast);

	/** 
	 * @brief Get bNewIsHideInPast
	*/
	bool GetIsHideInPast();
	
private:
	/** The color of the RainbowBox (int format) */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_Material)
	int32 iColor;

	/** The material instance */
	UPROPERTY(Transient, Replicated)
	UMaterialInstanceDynamic* MaterialInstanceDynamic;

	/** To know if the RainbowBox is in the past or in the futur and if it sould notify the other RainbowBoxHandler */
	bool bShouldNotify;
	/** To known if the RainbowBox is hidden by the player in the past */
	bool bIsHideInPast;

	/**
	* @brief Function called when iColor is changed by replication, change the color of the material instance
	*/
	UFUNCTION()
	void OnRep_Material();
};
