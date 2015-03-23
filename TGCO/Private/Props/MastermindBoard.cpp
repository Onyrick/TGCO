

#include "TGCO.h"
#include "MastermindBoard.h"


AMastermindBoard::AMastermindBoard(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void AMastermindBoard::AddForMemory(TArray<TEnumAsByte<ESolutionType::Type>> Proposal, TArray<int> Difference)
{
	if (LastProposals.Num() > 3)
	{
		for (int i = 0; i < 3; ++i)
		{
			LastProposals[i].ProposalField = LastProposals[i + 1].ProposalField;
			LastProposals[i].DifferenceField = LastProposals[i + 1].DifferenceField;
		}
	}
	LastProposals[LastProposals.Num()].ProposalField = Proposal;
	LastProposals[LastProposals.Num()].DifferenceField = Difference;

	UpdateBoardDisplay();
}

void AMastermindBoard::UpdateBoardDisplay_Implementation()
{

}