

#include "TGCO.h"
#include "Puzzle/BarrierColor.h"
#include "LightningSwitch.h"

ALightningSwitch::ALightningSwitch(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SwitchShape(TEXT("StaticMesh'/Game/StarterContent/Props/SM_CornerFrame.SM_CornerFrame'"));
	StaticMesh->SetStaticMesh(SwitchShape.Object);
	StaticMesh->SetWorldScale3D(FVector(8.f, 8.f, 8.0f));


	//for (int i = 0; i < 10; i++)
	//{
	//	ConstructorHelpers::FObjectFinder<UStaticMesh> DiodeMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere'"));
	//	UStaticMeshComponent* Diode = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this);

	//	auto MeshMat = Diode->GetMaterial(0);
	//	UMaterialInstanceDynamic * MaterialDynInstance = UMaterialInstanceDynamic::Create(MeshMat, this);
	//	if (m_vControledTerminals.Num()>i && m_vControledTerminals[i] != nullptr)
	//	{
	//		auto barCol = m_vControledTerminals[i]->eBarColor;
	//		MaterialDynInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetBarrierColor(barCol)));
	//	}
	//	else
	//	{
	//		MaterialDynInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetBarrierColor(EBarrierColor::VE_Blue)));
	//	}
	//	MaterialDynInstance->SetScalarParameterValue(FName(TEXT("Intensity")), 10000.f);
	//	Diode->SetMaterial(0, MaterialDynInstance);

	//	Diode->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));
	//	auto loc = GetActorLocation();

	//	/** Attach mesh component to each diode */
	//	Diode->SetStaticMesh(DiodeMesh.Object);

	//	/** Register each Diode component */
	//	Diode->RegisterComponentWithWorld(GetWorld());

	//	/** Attach each diode to root element */
	//	//Diode->AttachTo(RootComponent);
	//	Diode->SetVisibility(false, true);
	//	Diode->SetRelativeLocation(StaticMesh->RelativeLocation + FVector(0.0, Informers.Num(), 20));
	//	Diode->AttachTo(StaticMesh);


	//	AddOwnedComponent(Diode);
	//	Informers.Push(Diode);
	//}
}

bool ALightningSwitch::OnInteract()
{
	//TODO
	//TODO
	UE_LOG(LogDebug, Warning, TEXT("Interactible Lightning Switch"));
	for (auto Iter(m_vControledTerminals.CreateIterator()); Iter; Iter++)
	{
		if ((*Iter) != nullptr)
		{
			(*Iter)->ChangeActiveState();
		}
	}

	return true;
}
