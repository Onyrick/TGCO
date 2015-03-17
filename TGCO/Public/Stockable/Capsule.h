
#pragma once

#include "Stockable/Stockable.h"
#include "SolutionType.h"
#include "Capsule.generated.h"

/**
* @class	ACapsule
*
* @brief	A stockable capsule of solution
*
*/
UCLASS()
class TGCO_API ACapsule : public AStockable
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	ACapsule(const FObjectInitializer& ObjectInitializer);

	/**
	* @brief	Update bIsCurrentlyUsed value.
	*
	* @param	bNewIsCurrentlyUsed	The new value of bIsCurrentlyUsed.
	*/
	UFUNCTION(BlueprintCallable, Category = "Capsule")
	void UpdateIsCurrentlyUsed(bool bNewIsCurrentlyUsed);

	/**
	* @brief	Get bIsCurrentlyUsed value.
	*
	* @return bool bIsCurrentlyUsed value
	*/
	UFUNCTION(BlueprintCallable, Category = "Capsule")
	bool IsCurrentlyUsed();

	/**
	* @brief	Get the solution type of the capsule.
	*
	* @return TEnumAsByte<ESolutionType::Type> The solution type of the capsule
	*/
	UFUNCTION(BlueprintCallable, Category = "Capsule")
	TEnumAsByte<ESolutionType::Type> GetSolutionType();


public:
	/** The SolutionType of the capsule */
	UPROPERTY(EditAnywhere, Category = "Capsule")
	TEnumAsByte<ESolutionType::Type> SolutionType;

	/** To know if the capsule is already in used and can't be re-used */
	UPROPERTY(EditAnywhere, Category = "Capsule")
	bool bIsCurrentlyUsed;
};
