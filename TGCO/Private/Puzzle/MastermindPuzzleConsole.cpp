

#include "TGCO.h"
#include <ctime>
#include <cstdlib>
#include "Utils.h"
#include "MastermindPuzzleConsole.h"

AMastermindPuzzleConsole::AMastermindPuzzleConsole(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer),
bInGame(true)
{
	bReplicates = true;
	Solution = new ESolutionType::Type[4]();
	Proposal = new ESolutionType::Type[4]();

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere'"));

	Diode1 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode1"));
	Diode2 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode2"));
	Diode3 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode3"));
	Diode4 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode4"));

	Diode1->SetStaticMesh(StaticMesh.Object);
	Diode2->SetStaticMesh(StaticMesh.Object);
	Diode3->SetStaticMesh(StaticMesh.Object);
	Diode4->SetStaticMesh(StaticMesh.Object);

	Diode1->RegisterComponentWithWorld(GetWorld());
	Diode2->RegisterComponentWithWorld(GetWorld());
	Diode3->RegisterComponentWithWorld(GetWorld());
	Diode4->RegisterComponentWithWorld(GetWorld());

	Diode1->AttachTo(RootComponent);
	Diode2->AttachTo(RootComponent);
	Diode3->AttachTo(RootComponent);
	Diode4->AttachTo(RootComponent);

	AddOwnedComponent(Diode1);
	AddOwnedComponent(Diode2);
	AddOwnedComponent(Diode3);
	AddOwnedComponent(Diode4);

	// Init the solution
	TArray<int> RandomNumber = Utils::CreateRandomArrayOfSolution(4);

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
	MaterialInstance1 = UMaterialInstanceDynamic::Create(MeshMat, this);
	MeshMat = Diode2->GetMaterial(0);
	MaterialInstance2 = UMaterialInstanceDynamic::Create(MeshMat, this);
	MeshMat = Diode3->GetMaterial(0);
	MaterialInstance3 = UMaterialInstanceDynamic::Create(MeshMat, this);
	MeshMat = Diode4->GetMaterial(0);
	MaterialInstance4 = UMaterialInstanceDynamic::Create(MeshMat, this);

	SwitchDiodeOff();
}

void AMastermindPuzzleConsole::UpdateDiode(int* Difference)
{

	switch (Difference[0]){
	case -1:
		// Good for the player, bad for the tree
		MaterialInstance1->SetVectorParameterValue(FName(TEXT("Color")), FColor(30, 250, 30));
		break;
	case 0:
		// Exist in solution to destroy the tree, but not a this place
		MaterialInstance1->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 245, 87));
		break;
	case 1:
		// Bad for the player, good for the tree
		MaterialInstance1->SetVectorParameterValue(FName(TEXT("Color")), FColor(250, 30, 30));
		break;
	default:
		MaterialInstance1->SetVectorParameterValue(FName(TEXT("Color")), FColor(30, 250, 30));
		break;

	}
	switch (Difference[1]){
	case -1:
		MaterialInstance2->SetVectorParameterValue(FName(TEXT("Color")), FColor(30, 250, 30));
		break;
	case 0:
		MaterialInstance2->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 245, 87));
		break;
	case 1:
		MaterialInstance2->SetVectorParameterValue(FName(TEXT("Color")), FColor(250, 30, 30));
		break;
	default:
		MaterialInstance2->SetVectorParameterValue(FName(TEXT("Color")), FColor(30, 250, 30));
		break;

	}
	switch (Difference[2]){
	case -1:
		MaterialInstance3->SetVectorParameterValue(FName(TEXT("Color")), FColor(30, 250, 30));
		break;
	case 0:
		MaterialInstance3->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 245, 87));
		break;
	case 1:
		MaterialInstance3->SetVectorParameterValue(FName(TEXT("Color")), FColor(250, 30, 30));
		break;
	default:
		MaterialInstance3->SetVectorParameterValue(FName(TEXT("Color")), FColor(30, 250, 30));
		break;

	}
	switch (Difference[3]){
	case -1:
		MaterialInstance4->SetVectorParameterValue(FName(TEXT("Color")), FColor(30, 250, 30));
		break;
	case 0:
		MaterialInstance4->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 245, 87));
		break;
	case 1:
		MaterialInstance4->SetVectorParameterValue(FName(TEXT("Color")), FColor(250, 30, 30));
		break;
	default:
		MaterialInstance4->SetVectorParameterValue(FName(TEXT("Color")), FColor(30, 250, 30));
		break;

	}

	MaterialInstance1->SetScalarParameterValue(FName(TEXT("Intensity")), 10);
	MaterialInstance2->SetScalarParameterValue(FName(TEXT("Intensity")), 10);
	MaterialInstance3->SetScalarParameterValue(FName(TEXT("Intensity")), 10);
	MaterialInstance4->SetScalarParameterValue(FName(TEXT("Intensity")), 10);

	Diode1->SetMaterial(0, MaterialInstance1);
	Diode2->SetMaterial(0, MaterialInstance2);
	Diode3->SetMaterial(0, MaterialInstance3);
	Diode4->SetMaterial(0, MaterialInstance4);

}

void AMastermindPuzzleConsole::SwitchDiodeOn()
{	
	MaterialInstance1->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 255, 255));
	MaterialInstance1->SetScalarParameterValue(FName(TEXT("Intensity")), 10);
	Diode1->SetMaterial(0, MaterialInstance1);

	MaterialInstance2->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 255, 255));
	MaterialInstance2->SetScalarParameterValue(FName(TEXT("Intensity")), 10);
	Diode2->SetMaterial(0, MaterialInstance2);

	MaterialInstance3->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 255, 255));
	MaterialInstance3->SetScalarParameterValue(FName(TEXT("Intensity")), 10);
	Diode3->SetMaterial(0, MaterialInstance3);

	MaterialInstance4->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 255, 255));
	MaterialInstance4->SetScalarParameterValue(FName(TEXT("Intensity")), 10);
	Diode4->SetMaterial(0, MaterialInstance4);

}

void AMastermindPuzzleConsole::SwitchDiodeOff()
{
	MaterialInstance1->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 255, 255));
	MaterialInstance1->SetScalarParameterValue(FName(TEXT("Intensity")), 1);
	Diode1->SetMaterial(0, MaterialInstance1);

	MaterialInstance2->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 255, 255));
	MaterialInstance2->SetScalarParameterValue(FName(TEXT("Intensity")), 1);
	Diode2->SetMaterial(0, MaterialInstance2);

	MaterialInstance3->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 255, 255));
	MaterialInstance3->SetScalarParameterValue(FName(TEXT("Intensity")), 1);
	Diode3->SetMaterial(0, MaterialInstance3);

	MaterialInstance4->SetVectorParameterValue(FName(TEXT("Color")), FColor(255, 255, 255));
	MaterialInstance4->SetScalarParameterValue(FName(TEXT("Intensity")), 1);
	Diode4->SetMaterial(0, MaterialInstance4);

}

bool AMastermindPuzzleConsole::OnInteract()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			if (bInGame)
			{
				UE_LOG(LogTest, Warning, TEXT("Console activate"));
				PlayerController->SetViewTargetWithBlend(CameraPuzzle, 1.5, EViewTargetBlendFunction::VTBlend_EaseInOut, 1.0, true);
				EnableInput(PlayerController);
				PlayerController->SetIgnoreMoveInput(true);
				PlayerController->SetIgnoreLookInput(true);
				PlayerController->bShowMouseCursor = true;
				PlayerController->bEnableClickEvents = true;
				PlayerController->bEnableMouseOverEvents = true;

				SwitchDiodeOn();
				bInGame = false;
			}
			else
			{
				UE_LOG(LogTest, Warning, TEXT("Console desactivate"));
				ACharacter* PlayerCharacter = PlayerController->GetCharacter();
				PlayerController->SetViewTargetWithBlend(PlayerCharacter, 1.5, EViewTargetBlendFunction::VTBlend_EaseInOut, 1.0, true);
				DisableInput(PlayerController);
				PlayerController->SetIgnoreMoveInput(false);
				PlayerController->SetIgnoreLookInput(false);
				PlayerController->bShowMouseCursor = false;
				PlayerController->bEnableClickEvents = false;
				PlayerController->bEnableMouseOverEvents = false;
				SwitchDiodeOff();
				bInGame = true;
				QuitMastermindPuzzleConsole();

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

void AMastermindPuzzleConsole::SetProposalAt(ESolutionType::Type NewProposal, int32 Index)
{
	Proposal[Index] = NewProposal;
}

void AMastermindPuzzleConsole::RemoveProposalAt(int32 Index)
{
	Proposal[Index] = ESolutionType::NONE ;
}

ESolutionType::Type AMastermindPuzzleConsole::GetProposalAt(int32 Index)
{
	return Proposal[Index];
}


void AMastermindPuzzleConsole::ClearProposal()
{
	for (int i = 0; i < 4; ++i)
	{
		Proposal[i] = ESolutionType::NONE;
	}
}