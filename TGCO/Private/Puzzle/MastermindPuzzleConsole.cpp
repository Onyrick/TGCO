

#include "TGCO.h"
#include <ctime>
#include <cstdlib>
#include "Utils.h"
#include "MastermindPuzzleConsole.h"

AMastermindPuzzleConsole::AMastermindPuzzleConsole(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Solution = new ESolutionType::Type[4]();

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("MaterialInstanceConstant'/Game/Blueprints/AI/MonstroPlante/Mat_Emissive'"));
	MaterialInstance1 = UMaterialInstanceDynamic::Create(Material.Object, this);
	MaterialInstance2 = UMaterialInstanceDynamic::Create(Material.Object, this);
	MaterialInstance3 = UMaterialInstanceDynamic::Create(Material.Object, this);
	MaterialInstance4 = UMaterialInstanceDynamic::Create(Material.Object, this);

	Diode1 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode1"));
	Diode2 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode2"));
	Diode3 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode3"));
	Diode4 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Diode4"));

	Diode1->SetStaticMesh(StaticMesh.Object);
	Diode2->SetStaticMesh(StaticMesh.Object);
	Diode3->SetStaticMesh(StaticMesh.Object);
	Diode4->SetStaticMesh(StaticMesh.Object);

	Diode1->SetMaterial(0, MaterialInstance1);
	Diode2->SetMaterial(0, MaterialInstance2);
	Diode3->SetMaterial(0, MaterialInstance3);
	Diode4->SetMaterial(0, MaterialInstance4);

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

	UpdateDiode();
}

void AMastermindPuzzleConsole::UpdateDiode()
{
	MaterialInstance1->SetVectorParameterValue(FName(TEXT("Color")), FColor(226, 230, 93));
	MaterialInstance2->SetVectorParameterValue(FName(TEXT("Color")), FColor(226, 230, 93));
	MaterialInstance3->SetVectorParameterValue(FName(TEXT("Color")), FColor(226, 230, 93));
	MaterialInstance4->SetVectorParameterValue(FName(TEXT("Color")), FColor(226, 230, 93));

	Diode1->SetMaterial(0, MaterialInstance1);
	Diode2->SetMaterial(0, MaterialInstance2);
	Diode3->SetMaterial(0, MaterialInstance3);
	Diode4->SetMaterial(0, MaterialInstance4);

}

void AMastermindPuzzleConsole::CreatePuzzle()
{
	int NbSolution = GetNumberOfSolution();

	srand(time(NULL));

	// Init the solution
	TArray<int> RandomNumber = Utils::InitWhithoutDuplication(NbSolution);
	Utils::Blend(RandomNumber);
	for (int i = 0; i < 4; ++i)
	{
		Solution[i] = GetSolutionFromInt(RandomNumber[i]);
	}
}

bool AMastermindPuzzleConsole::OnInteract()
{
	//TODO
	UE_LOG(LogTest, Warning, TEXT("Console activate"));
	return true;
}

int* AMastermindPuzzleConsole::SubmitAnswer(ESolutionType::Type* Answer)
{
	// -1 : doesn't exist in solution
	// 0 : exist but not in right place
	// 1 : in the right place
	int* Difference = new int[4]();

	// For each number of the answer
	for (int i = 0; i < 4; ++i)
	{
		// If it matches the solution
		if (Answer[i] == Solution[i])
		{
			Difference[i] = 1;
		}
		else
		{
			// Check if it is somewhere else in the solution
			bool ExistElsewhere = false;
			for (int j = 0; j < 4; ++j)
			{
				if (Answer[i] == Solution[j])
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
	return Difference;
}


