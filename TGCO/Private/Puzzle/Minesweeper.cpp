

#include "TGCO.h"
#include "ConsoleMinesweeper.h"
#include "Minesweeper.h"
#include "UnrealMathUtility.h"

AMinesweeper::AMinesweeper(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<AMinesweeperBox> ItemBlueprint(TEXT("/Game/Blueprints/MinesweeperBox_BP"));
	if (ItemBlueprint.Class != nullptr)
	{
		MinesweeperBoxBP = (UClass*)ItemBlueprint.Class;
	}
	bReplicates = true;
}

void AMinesweeper::CreateMinesweeper()
{
	//Create all the MinesweeperBox and initialize them without mine
	//UE_LOG(LogTest, Warning, TEXT("Je suis dans la fonction CreateMinesweeper"));
	// TODO : Works with non squares datas (NB_COL != NB_ROWS), Make size of minesweeper box a constant int for future changement !
	// TODO : Works with a custom angle instead of 90
	for (int i = 0; i < SIZE; ++i)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			unsigned int x = i / NB_COL;
			unsigned int y = i % NB_COL;
			FVector SpawnLocation = FVector(x * 405, y * 405, 5.0);
			const FRotator SpawnRotation = GetActorRotation();
			SpawnLocation = SpawnLocation.RotateAngleAxis(90, FVector(0, 0, 1));
			SpawnLocation = GetActorLocation() + SpawnLocation;

			AMinesweeperBox* m = (AMinesweeperBox*)World->SpawnActor<AMinesweeperBox>(MinesweeperBoxBP, SpawnLocation, SpawnRotation);
			Squares.Add(m);
		}
	}

	PutMinesRandomly();
	CalculateNeighboursUndermined();
	UE_LOG(LogTest, Warning, TEXT("After CalculateNeighboursUndermined"));
}

bool AMinesweeper::ServerResetMinesweeper_Validate()
{
	return true;
}

void AMinesweeper::ServerResetMinesweeper_Implementation()
{
	//UE_LOG(LogTest, Warning, TEXT("Je suis dans ServerResetMinesweeper"));
	ResetMinesweeper();
}

void AMinesweeper::ResetMinesweeper()
{
	//UE_LOG(LogTest, Warning, TEXT("Début de ResetMinesweeper"));
	if (Role < ROLE_Authority)
	{
		//UE_LOG(LogTest, Warning, TEXT("Pas autorité, appel de ServerResetMinesweeper"));
		ServerResetMinesweeper();
	}
	else
	{
		//UE_LOG(LogTest, Warning, TEXT("ResetMinesweeper logic from Server"));
		if (Squares.Num() == 0)
		{
			//UE_LOG(LogTest, Warning, TEXT("Appel de CreateMinesweeper car square.num() == 0"));
			CreateMinesweeper();
		}
		else
		{
			//DeleteMinesweeper();
			for (int i = 0; i < Squares.Num(); ++i)
			{
				Squares[i]->Destroy();
			}
			Squares.Empty(Squares.Num());
			CreateMinesweeper();

			for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				if (ActorItr->GetName().Contains("MinesweeperConsole") && ActorItr->GetActorClass()->GetDescription() == FString(TEXT("Minesweeper Console BP")))
				{
					UE_LOG(LogTest, Warning, TEXT("Call Reset Minesweeper on MinesweeperConsole"));
					AConsoleMinesweeper* ConsoleMinesweeper = Cast<AConsoleMinesweeper>(*ActorItr);
					ConsoleMinesweeper->ResetMinesweeper();
				}
			}
		}
	}

	
}

void AMinesweeper::PutMinesRandomly()
{
	//UE_LOG(LogTest, Warning, TEXT("Je suis dans la fonction PutMinesRandomly"));
	int iSecret;
	srand(time(nullptr));
	for (int cpt = 0; cpt < NB_MINES; ++cpt)
	{
		do
		{ 
			iSecret = FMath::RandRange(1, SIZE - 2); 
		} 
		while	(	Squares[iSecret]->GetIsUndermined() == true || 
					Squares[iSecret + 1]->GetIsUndermined() == true || 
					Squares[iSecret - 1]->GetIsUndermined() == true		);
		
		Squares[iSecret]->SetIsUndermined();
	}
}

void AMinesweeper::CalculateNeighboursUndermined()
{
	UE_LOG(LogTest, Warning, TEXT("Je suis dans la fonction CalculateNeighboursUndermined"));
	// TODO : Make it works with NB_COL != NB_ROWS, launch some exceptions ...
	//For all MinesweeperBox
	for (int i = 0; i < SIZE; ++i)
	{
		UE_LOG(LogTest, Warning, TEXT("for i"));
		//Check the neighbors
		for (int j = -1; j <= 1; ++j)
		{
			UE_LOG(LogTest, Warning, TEXT("for j"));
			// If the MinesweeperBox is at the beginning of a row, don't check the previous one. 
			// And if it is at the end of the row, don't check the next one.
			if (((i%NB_COL == 0) && (j == -1)) 
				|| ((i%NB_COL == NB_COL - 1) && (j == 1)) )
			{
				continue;
			}
			// Check the neighbors up
			if ((i/NB_COL > 0) && (Squares[i - NB_COL + j]->GetIsUndermined() == true))
			{
				Squares[i]->SetNeighboursUndermined();
			}
			// Check the neighbors on the left and on the right
			if ((j != 0) && (Squares[i + j]->GetIsUndermined() == true))
			{
				Squares[i]->SetNeighboursUndermined();
			}
			// Check the neighbors down
			if ((i / NB_COL < NB_COL-1) && (Squares[i + NB_COL + j]->GetIsUndermined() == true))
			{
				Squares[i]->SetNeighboursUndermined();
			}
		}
	}
}

int32 AMinesweeper::GetMinesweeperSize()
{
	return SIZE;
}

AMinesweeperBox* AMinesweeper::GetMinesweeperBoxAt(int32 index)
{
	if (index >= SIZE) { return nullptr; }

	return Squares[index];
}

void AMinesweeper::OnResetConsole()
{
	if (Role < ROLE_Authority)
	{
		UE_LOG(LogTest, Warning, TEXT("Authority"));
	}
	else
	{
		UE_LOG(LogTest, Warning, TEXT("No Authority"));
	}
	for (int i = 0; i < SIZE; ++i)
	{
		if (Squares[i]->IsMarked())
		{
			Squares[i]->SetVisibilityOfFlag();
		}
	}
}


void AMinesweeper::DeleteMinesweeper()
{
	for (int i = 0; i < Squares.Num(); ++i)
	{
		Squares[i]->Destroy();
	}
	Squares.Empty(Squares.Num());
}
