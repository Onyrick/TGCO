

#include "TGCO.h"
#include "Puzzle/BarrierColor.h"
#include "LightningSwitch.h"

ALightningSwitch::ALightningSwitch(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SwitchShape(TEXT("StaticMesh'/Game/StarterContent/Props/SM_CornerFrame.SM_CornerFrame'"));
	StaticMesh->SetStaticMesh(SwitchShape.Object);
	StaticMesh->SetWorldScale3D(FVector(8.f, 8.f, 8.0f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> DiodeMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere'"));

	Diode1 = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this);

	Diode1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	/** Attach mesh component to each diode */
	Diode1->SetStaticMesh(DiodeMesh.Object);

	/** Register each Diode component */
	Diode1->RegisterComponentWithWorld(GetWorld());

	/** Attach each diode to root element */
	//Diode->AttachTo(RootComponent);
	Diode1->SetVisibility(true, true);
	Diode1->SetRelativeLocation(StaticMesh->RelativeLocation + FVector(0.0, 0, 20));
	Diode1->AttachTo(StaticMesh);


	auto MeshMat = Diode1->GetMaterial(0);
	UMaterialInstanceDynamic * MaterialDynInstance = UMaterialInstanceDynamic::Create(MeshMat, this);
	MaterialDynInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetBarrierColor(EBarrierColor::VE_Blue)));
	MaterialDynInstance->SetScalarParameterValue(FName(TEXT("Intensity")), 10000.f);

	Diode1->SetMaterial(0, MaterialDynInstance);

	AddOwnedComponent(Diode1);
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

	if (Diode1 != nullptr)
	{
		auto MeshMat = Diode1->GetMaterial(0);
		UMaterialInstanceDynamic * MaterialDynInstance = UMaterialInstanceDynamic::Create(MeshMat, this);
		if (m_vControledTerminals[0] != nullptr)
		{
			auto barCol = m_vControledTerminals[0]->eBarColor;
			MaterialDynInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetBarrierColor(barCol)));
		}
		else
		{
			MaterialDynInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetBarrierColor(EBarrierColor::VE_Blue)));
		}
		MaterialDynInstance->SetScalarParameterValue(FName(TEXT("Intensity")), 10000.f);
		Diode1->SetMaterial(0, MaterialDynInstance);

	}
	return true;
}
