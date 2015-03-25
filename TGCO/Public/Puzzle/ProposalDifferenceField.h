
#include "ProposalDifferenceField.generated.h"

struct FProposalDifferenceField
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mastermind)
	TArray<TEnumAsByte<ESolutionType::Type>> ProposalField;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mastermind)
	TArray<int32> DifferenceField;

	FProposalDifferenceField()
	{
	}
};
