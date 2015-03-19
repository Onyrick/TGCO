
#include "TGCO.h"
#include <ctime>
#include <cstdlib>
#include "Utils.h"
#include "MastermindPuzzleConsole.h"
#include "TGCOPlayerState.h"

AMastermindPuzzleConsole::AMastermindPuzzleConsole(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bReplicates = true;
	Solution = new ESolutionType::Type[4]();
	Proposal = new ESolutionType::Type[4]();
	MaterialArray = TArray<UMaterialInstanceDynamic*>();

	/** Create static mesh for diode */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere'"));

	/** Create mesh component for each diode */
	Diode1 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode1"));
	Diode2 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode2"));
	Diode3 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode3"));
	Diode4 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode4"));

	/** Attach mesh component to each diode */
	Diode1->SetStaticMesh(StaticMesh.Object);
	Diode2->SetStaticMesh(StaticMesh.Object);
	Diode3->SetStaticMesh(StaticMesh.Object);
	Diode4->SetStaticMesh(StaticMesh.Object);

	/** Register each Diode component */
	Diode1->RegisterComponentWithWorld(GetWorld());
	Diode2->RegisterComponentWithWorld(GetWorld());
	Diode3->RegisterComponentWithWorld(GetWorld());
	Diode4->RegisterComponentWithWorld(GetWorld());

	/** Attach each diode to root element */
	Diode1->AttachTo(RootComponent);
	Diode2->AttachTo(RootComponent);
	Diode3->AttachTo(RootComponent);
	Diode4->AttachTo(RootComponent);

	AddOwnedComponent(Diode1);
	AddOwnedComponent(Diode2);
	AddOwnedComponent(Diode3);
	AddOwnedComponent(Diode4);

	// Init the solution
	TArray<int> RandomNumber = CreateRandomArrayOfSolution(4);

	for (int i = 0; i < 4; ++i)
	{
		Solution[i] = GetSolutionFromInt(RandomNumber[i]);
		UE_LOG(LogTest, Warning, TEXT("Solution %i : %s"), i, *GetNameOfTheSolution(Solution[i]));
	}
}

void AMastermindPuzzleConsole::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInterface* MeshMat = Diode1->GetMaterial(0);
	MaterialArray.Push(UMaterialInstanceDynamic::Create(MeshMat, this));
	MeshMat = Diode2->GetMaterial(0);
	MaterialArray.Push(UMaterialInstanceDynamic::Create(MeshMat, this));
	MeshMat = Diode3->GetMaterial(0);
	MaterialArray.Push(UMaterialInstanceDynamic::Create(MeshMat, this));
	MeshMat = Diode4->GetMaterial(0);
	MaterialArray.Push(UMaterialInstanceDynamic::Create(MeshMat, this));

	SwitchDiodeOff();
}

TArray<int32> AMastermindPuzzleConsole::CreateRandomArrayOfSolution(int32 iSize)
{
	TArray<int32> Result = TArray<int32>();
	srand(time(NULL));
	bool bAlreadyExist;
	bool bRetry = true;
	int iRandomNumber;

	for (int i = 0; i < iSize; ++i)
	{
		do
		{
			bAlreadyExist = false;
			iRandomNumber = rand() % (iSize + 1);
			for (int j = 0; j < Result.Num(); ++j)
			{
				if (Result[j] == iRandomNumber)
				{
					bAlreadyExist = true;
				}
			}
		} while (bAlreadyExist);

		Result.Add(iRandomNumber);
	}
	return Result;
}

void AMastermindPuzzleConsole::UpdateDiode(int* Difference)
{
	for (int i = 0; i < MaterialArray.Num(); ++i)
	{

		UMaterialInstanceDynamic* MaterialInstance = MaterialArray[i];
		switch (Difference[i]){
			case -1:
				// Good for the player, bad for the tree
				MaterialInstance->SetVectorParameterValue(FName(TEXT("Color")), FColor(30, 250, 30));
				break;
			case 0:
				// Exist in solution to destroy the tree, but not a this place
				MaterialInstance->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 245, 87));
				break;
			case 1:
				// Bad for the player, good for the tree
				MaterialInstance->SetVectorParameterValue(FName(TEXT("Color")), FColor(250, 30, 30));
				break;
			default:
				MaterialInstance->SetVectorParameterValue(FName(TEXT("Color")), FColor(30, 250, 30));
				break;

		}
		MaterialInstance->SetScalarParameterValue(FName(TEXT("Intensity")), 10);
	}

	Diode1->SetMaterial(0, MaterialArray[0]);
	Diode2->SetMaterial(0, MaterialArray[1]);
	Diode3->SetMaterial(0, MaterialArray[2]);
	Diode4->SetMaterial(0, MaterialArray[3]);

}

void AMastermindPuzzleConsole::SwitchDiodeOn()
{
	// Change color to white
	for (int i = 0; i < MaterialArray.Num(); ++i)
	{
		UMaterialInstanceDynamic* MaterialInstance = MaterialArray[i];
		MaterialInstance->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 255, 255));
		MaterialInstance->SetScalarParameterValue(FName(TEXT("Intensity")), 10);
	}
	Diode1->SetMaterial(0, MaterialArray[0]);
	Diode2->SetMaterial(0, MaterialArray[1]);
	Diode3->SetMaterial(0, MaterialArray[2]);
	Diode4->SetMaterial(0, MaterialArray[3]);

}

void AMastermindPuzzleConsole::SwitchDiodeOff()
{

	for (int i = 0; i < MaterialArray.Num(); ++i)
	{
		UMaterialInstanceDynamic* MaterialInstance = MaterialArray[i];
		MaterialInstance->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 255, 255));
		MaterialInstance->SetScalarParameterValue(FName(TEXT("Intensity")), 1);
	}
	Diode1->SetMaterial(0, MaterialArray[0]);
	Diode2->SetMaterial(0, MaterialArray[1]);
	Diode3->SetMaterial(0, MaterialArray[2]);
	Diode4->SetMaterial(0, MaterialArray[3]);

}

bool AMastermindPuzzleConsole::OnInteract()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			ATGCOPlayerState* PlayerState = Cast<ATGCOPlayerState>(PlayerController->PlayerState);
			if (PlayerState)
			{
				if (PlayerState->eCurrentState == EPlayerStatus::IN_GAME)
				{
					PlayerState->SwitchGamePuzzle(CameraPuzzle);
					SwitchDiodeOn();
				}
				else
				{
					if (PlayerState->eCurrentState == EPlayerStatus::IN_PUZZLE_GAME)
					{
						PlayerState->SwitchGamePuzzle(PlayerController->GetCharacter());
						SwitchDiodeOff();
					}
				}
			}
		}
	}
	return true;
}

void AMastermindPuzzleConsole::SubmitAnswer()
{
	// -1 : doesn't exist in solution
	// 0 : exist but not in right place
	// 1 : in the right place
	int* Difference = new int[4]();

	// For each number of the answer
	for (int i = 0; i < 4; ++i)
	{
		// If it matches the solution
		if (Proposal[i] == Solution[i])
		{
			Difference[i] = 1;
		}
		else
		{
			// Check if it is somewhere else in the solution
			bool ExistElsewhere = false;
			for (int j = 0; j < 4; ++j)
			{
				if (Proposal[i] == Solution[j])
				{
					Difference[i] = 0;
					ExistElsewhere = true;
					break;
				}
			}
			if (!ExistElsewhere)
			{
				Difference[i] = -1;
			}
		}
	}
	UE_LOG(LogTest, Warning, TEXT("Solution : %s, %s, %s, %s"), *GetNameOfTheSolution(Solution[0]), *GetNameOfTheSolution(Solution[1]), *GetNameOfTheSolution(Solution[2]), *GetNameOfTheSolution(Solution[3]));
	UE_LOG(LogTest, Warning, TEXT("Proposal : %s, %s, %s, %s"), *GetNameOfTheSolution(Proposal[0]), *GetNameOfTheSolution(Proposal[1]), *GetNameOfTheSolution(Proposal[2]), *GetNameOfTheSolution(Proposal[3]));
	UE_LOG(LogTest, Warning, TEXT("Difference : %d, %d, %d, %d"), Difference[0], Difference[1], Difference[2], Difference[3]);

	UpdateDiode(Difference);
	
	//return Difference;
}

void AMastermindPuzzleConsole::SetProposalAt(ESolutionType::Type NewProposal, int32 iIndex)
{
	Proposal[iIndex] = NewProposal;
}

void AMastermindPuzzleConsole::RemoveProposalAt(int32 iIndex)
{
	Proposal[iIndex] = ESolutionType::NONE ;
}

ESolutionType::Type AMastermindPuzzleConsole::GetProposalAt(int32 iIndex)
{
	return Proposal[iIndex];
}


void AMastermindPuzzleConsole::ClearProposal()
{
	for (int i = 0; i < 4; ++i)
	{
		Proposal[i] = ESolutionType::NONE;
	}
}
