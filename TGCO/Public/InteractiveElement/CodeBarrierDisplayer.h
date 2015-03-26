

#pragma once
#include "InteractiveElement/InteractiveElement.h"
#include <string>
#include "CodeBarrierDisplayer.generated.h"

/**
 * @class ACodeBarrierDisplayer
 *
 * 	@brief Class representing a display terminal on which the future player
 * will read a code that the past player will use to deactivate all the electrical barrier
 * in the corridor
 * 
 */
class AOpenBarrierConsole;
UCLASS()
class TGCO_API ACodeBarrierDisplayer : public AInteractiveElement
{
	GENERATED_BODY()

public:

	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	ACodeBarrierDisplayer(const FObjectInitializer& ObjectInitializer);


	/**
	* @brief	Displays the code to deactivate the barriers
	*
	* @returns	bool.
	*/
	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		virtual bool OnInteract() override;

	/**
	* @brief	The code to that deactivates the barriers
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenBarrier")
		FString CodeToDisplay;

	/**
	* @brief	Sets the code
	*
	* @param	FString	The code to display
	* @return   void
	*/
	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		void SetCodeToDisplay(FString code);

	
	/**
	* @brief	Sends a custom event so that the widget that will display
	* the information knows that it can look it up in its associated displayer
	*
	* @return void
	*/
	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		void SendCodeReadyEvent();

	/**@brief The Custom event informing that the code is ready to be read*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableEvent_CodeDisplay);

	/** @brief The event that is broadcasted when the code is set */
	UPROPERTY(BlueprintAssignable, Replicated, Category = "OpenBarrier")
		FBindableEvent_CodeDisplay CodeReadyToDisplay;

private:
	/**
	* @brief	The code that deactivate the barriers (in string for debug purpose)
	*/
	std::string codeinstring;
};
