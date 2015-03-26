

#pragma once
#include "InteractiveElement/InteractiveElement.h"
#include <string>
#include "CodeBarrierDisplayer.generated.h"
/**
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
	*/
	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		virtual bool OnInteract() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenBarrier")
		FString CodeToDisplay;

	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		void SetCodeToDisplay(FString code);

	UFUNCTION(BlueprintCallable, Category = "OpenBarrier")
		void SendCodeReadyEvent();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBindableEvent_CodeDisplay);

	/** @brief The event that is broadcasted when you have to show the tree */
	UPROPERTY(BlueprintAssignable, Replicated, Category = "OpenBarrier")
		FBindableEvent_CodeDisplay CodeReadyToDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OpenBarrier")
		AOpenBarrierConsole* MyParent;


private:
	std::string codeinstring;
};
