

#pragma once
#include <vector>

#include "InteractiveElement/InteractiveElement.h"
#include "Props/LightningBarrier.h"
#include "LightningSwitch.generated.h"

/**
 * @brief Switch allowing the player to turn off a @ref ALightningBarrier (either a simple one
 * or part of a @ref AMultiLightningBarrier
 *
 * 	@sa AInteractiveElement
 */
UCLASS()
class TGCO_API ALightningSwitch : public AInteractiveElement
{

	GENERATED_BODY()

public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	ALightningSwitch(const FObjectInitializer& ObjectInitializer);

	/**
	* @brief	Called when the Player uses the object 
	*
	* @return	void
	*/
	UFUNCTION(BlueprintCallable, Category = "LightningSwitch")
		virtual void BeginPlay() override;

	/**
	* @brief	Called when the Player uses the object 
	*
	* @return	bool
	*/
	UFUNCTION(BlueprintCallable, Category = "LightningSwitch")
		virtual bool OnInteract() override;

	/** Array containing pointers to all the barrier it controls */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightningSwitch")
		TArray<ALightningBarrier *> m_vControledTerminals;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightningSwitch")
	/** List of diode representing the controlled barrier. Because of a problem of TArray those are hard set 
	values but will be changed to dynamic as soon as the bug is solved*/
	UStaticMeshComponent* Diode1;
	UStaticMeshComponent* Diode2;
	UStaticMeshComponent* Diode3;


private:

};
