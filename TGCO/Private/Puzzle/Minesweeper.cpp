

#include "TGCO.h"
#include "ConsoleMinesweeper.h"
#include "Minesweeper.h"

AMinesweeper::AMinesweeper(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/MinesBox_BP'"));
	//if (ItemBlueprint.Object){
	static ConstructorHelpers::FClassFinder<AMinesBox> ItemBlueprint(TEXT("/Game/Blueprints/MineBox_BP"));
	if (ItemBlueprint.Class != nullptr)
	{
		MineBoxBP = (UClass*)ItemBlueprint.Class;
	}
	bReplicates = true;
}

void AMinesweeper::CreateMinesweeper()
{
	//Create all the MinesBox and initialize them without mine
	//UE_LOG(LogTest, Warning, TEXT("Je suis dans la fonction CreateMinesweeper"));
	for (int i = 0; i < SIZE; ++i)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			unsigned int x = i / NB_COL;
			unsigned int y = i % NB_COL;
			const FVector SpawnLocation = GetActorLocation() + FVector(x * 405, y * 405, 5.0);
			const FRotator SpawnRotation = GetActorRotation();
			AMinesBox* m = (AMinesBox*)World->SpawnActor<AMinesBox>(MineBoxBP, SpawnLocation, SpawnRotation);
			Squares.Add(m);
		}
	}

	PutMinesRandomly();
	CalculateNeighboursUndermined();

	
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains("ConsoleMinesweeper") && ActorItr->GetActorClass()->GetDescription() == FString(TEXT("Console Minesweeper BP")))
		{
			AConsoleMinesweeper* ConsoleMinesweeper = Cast<AConsoleMinesweeper>(*ActorItr);
			ConsoleMinesweeper->ResetMinesweeper();
		}
	}
	
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
			for (int i = 0; i < Squares.Num(); ++i)
			{
				Squares[i]->Destroy();
			}
			Squares.Empty(Squares.Num());
			CreateMinesweeper();
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
		//UE_LOG(LogTest, Warning, TEXT("Passe dans la boucle du nombre de mine : %d"), cpt);
		iSecret = rand() % SIZE;
		if (Squares[iSecret]->GetIsUndermined() != true)
		{
			//UE_LOG(LogTest, Warning, TEXT("Je met une mine sur la square"));
			Squares[iSecret]->SetIsUndermined();
		}
		else
		{
			--cpt;
		}
	}
}

void AMinesweeper::CalculateNeighboursUndermined()
{
	//UE_LOG(LogTest, Warning, TEXT("Je suis dans la fonction CalculateNeighboursUndermined"));
	//For all MineBox
	for (int i = 0; i < SIZE; ++i)
	{
		//Check the neighbours
		for (int j = -1; j <= 1; ++j)
		{
			// If the MineBox is at the beginning of a row, don't check the previous one. 
			// And if it is at the end of the row, don't check the next one.
			if (((i%NB_COL == 0) && (j == -1)) 
				|| ((i%NB_COL == NB_COL - 1) && (j == 1)) )
			{
				continue;
			}
			// Check the neighbours up
			if ((i/NB_COL > 0) && (Squares[i - NB_COL + j]->GetIsUndermined() == true))
			{
				Squares[i]->SetNeighboursUndermined();
			}
			// Check the neighbours on the left and on the right
			if ((j != 0) && (Squares[i + j]->GetIsUndermined() == true))
			{
				Squares[i]->SetNeighboursUndermined();
			}
			// Check the neighbours down
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

AMinesBox* AMinesweeper::GetMineBoxAt(int32 index)
{
	if (index > SIZE) return nullptr;

	return Squares[index];
}


void AMinesweeper::DeleteMinesweeper()
{
	Squares.Empty();
}
