

#include "TGCO.h"
#include "MastermindBoard.h"


AMastermindBoard::AMastermindBoard(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void AMastermindBoard::AddForMemory(TArray<TEnumAsByte<ESolutionType::Type>> Proposal, TArray<int> Difference)
{

	UE_LOG(LogTest, Warning, TEXT("LastProposal sizeLastProposals.Num() : %d"), LastProposals.Num());
	if (LastProposals.Num() > 3)
	{
		for (int i = 0; i < 3; ++i)
		{
			UE_LOG(LogTest, Warning, TEXT("LastProposal : %d"), i);
			LastProposals[i].ProposalField = LastProposals[i + 1].ProposalField;
			LastProposals[i].DifferenceField = LastProposals[i + 1].DifferenceField;
		}
		LastProposals.RemoveAt(3);
	}
	FProposalDifferenceField pdf = FProposalDifferenceField(Proposal, Difference);
	LastProposals.Add(pdf);
	//LastProposals[LastProposals.Num()].ProposalField = Proposal;
	//LastProposals[LastProposals.Num()].DifferenceField = Difference;

	UpdateBoardDisplay();
}

void AMastermindBoard::UpdateBoardDisplay_Implementation()
{

}