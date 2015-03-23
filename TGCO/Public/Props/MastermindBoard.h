
#pragma once

#include "GameFramework/Actor.h"
#include "SolutionType.h"
#include "MastermindBoard.generated.h"

/**
* @brief Structure to permit to store array of array. Comport a proposal field and a difference field.
*/
USTRUCT()
struct FProposalDifferenceField
{
	GENERATED_USTRUCT_BODY()

	/** The proposal field */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mastermind)
	TArray<TEnumAsByte<ESolutionType::Type>> ProposalField;

	/** The difference field */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mastermind)
	TArray<int32> DifferenceField;

	FProposalDifferenceField()
	{
	}
};

/**
 * @brief A board to display the fourth previous proposal of the player.
 */
UCLASS()
class TGCO_API AMastermindBoard : public AActor
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	AMastermindBoard(const FObjectInitializer& ObjectInitializer);

	/**
	* @brief Add the proposal for memory.
	* 
	* @param Proposal The proposal to add
	* @param Difference The difference associated
	*/
	void AddForMemory(TArray<TEnumAsByte<ESolutionType::Type>> Proposal, TArray<int> Difference);

	/**
	* @brief Update the display on the board
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Mastermind")
	void UpdateBoardDisplay();
	

protected:
	
	/** Array of last proposal of the player with differences */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mastermind)
	TArray<FProposalDifferenceField> LastProposals;

	
};
