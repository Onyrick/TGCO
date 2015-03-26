

#include "TGCO.h"
#include "Puzzle/BarrierColor.h"
#include "LightningSwitch.h"

ALightningSwitch::ALightningSwitch(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/*Creation of the switch mesh*/
	ConstructorHelpers::FObjectFinder<UStaticMesh> SwitchShape(TEXT("StaticMesh'/Game/StarterContent/Props/SM_CornerFrame.SM_CornerFrame'"));
	StaticMesh->SetStaticMesh(SwitchShape.Object);
	StaticMesh->SetWorldScale3D(FVector(8.f, 8.f, 8.0f));

	/*Creation of the diodes mesh*/
	ConstructorHelpers::FObjectFinder<UStaticMesh> DiodeMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere'"));
	Diode1 = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this);
	Diode1->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	/** Attach mesh component to each diode */
	Diode1->SetStaticMesh(DiodeMesh.Object);

	/** Register each Diode component */
	Diode1->RegisterComponentWithWorld(GetWorld());

	/** Attach each diode to root element */
	//Diode->AttachTo(RootComponent);
	Diode1->SetVisibility(false, true);
	Diode1->SetRelativeLocation(StaticMesh->RelativeLocation + FVector(0.0, 0, 20));
	Diode1->AttachTo(StaticMesh);

	Diode2 = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this);
	Diode2->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	/** Attach mesh component to each diode */
	Diode2->SetStaticMesh(DiodeMesh.Object);

	/** Register each Diode component */
	Diode2->RegisterComponentWithWorld(GetWorld());

	/** Attach each diode to root element */
	//Diode->AttachTo(RootComponent);
	Diode2->SetVisibility(false, true);
	Diode2->SetRelativeLocation(StaticMesh->RelativeLocation + FVector(0.0, 1, 20));
	Diode2->AttachTo(StaticMesh);

	Diode3 = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this);
	Diode3->SetWorldScale3D(FVector(0.01f, 0.01f, 0.01f));

	/** Attach mesh component to each diode */
	Diode3->SetStaticMesh(DiodeMesh.Object);

	/** Register each Diode component */
	Diode3->RegisterComponentWithWorld(GetWorld());

	/** Attach each diode to root element */
	//Diode->AttachTo(RootComponent);
	Diode3->SetVisibility(false, true);
	Diode3->SetRelativeLocation(StaticMesh->RelativeLocation + FVector(0.0, 2, 20));
	Diode3->AttachTo(StaticMesh);


	AddOwnedComponent(Diode1);
}

void ALightningSwitch::BeginPlay()
{
	Super::BeginPlay();
	/*First thing the switch does on start is setting the color of its diodes to their
	matching indexed barrier*/
	if (Diode1 != nullptr && m_vControledTerminals.Num() > 0)
	{
		auto MeshMat = Diode1->GetMaterial(0);
		UMaterialInstanceDynamic * MaterialDynInstance = UMaterialInstanceDynamic::Create(MeshMat, this);
		if (m_vControledTerminals[0] != nullptr)
		{
			auto barCol = m_vControledTerminals[0]->eBarColor;
			MaterialDynInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetBarrierColor(barCol)));
		}
		Diode1->SetVisibility(true, true);
		MaterialDynInstance->SetScalarParameterValue(FName(TEXT("Intensity")), 10000.f);
		Diode1->SetMaterial(0, MaterialDynInstance);
	}
	if (Diode2 != nullptr && m_vControledTerminals.Num() > 1)
	{
		auto MeshMat = Diode2->GetMaterial(0);
		UMaterialInstanceDynamic * MaterialDynInstance = UMaterialInstanceDynamic::Create(MeshMat, this);
		if (m_vControledTerminals[1] != nullptr)
		{
			auto barCol = m_vControledTerminals[1]->eBarColor;
			MaterialDynInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetBarrierColor(barCol)));
		}
		Diode2->SetVisibility(true, true);
		MaterialDynInstance->SetScalarParameterValue(FName(TEXT("Intensity")), 10000.f);
		Diode2->SetMaterial(0, MaterialDynInstance);
	}
	if (Diode3 != nullptr && m_vControledTerminals.Num() > 2)
	{
		auto MeshMat = Diode3->GetMaterial(0);
		UMaterialInstanceDynamic * MaterialDynInstance = UMaterialInstanceDynamic::Create(MeshMat, this);
		if (m_vControledTerminals[2] != nullptr)
		{
			auto barCol = m_vControledTerminals[2]->eBarColor;
			MaterialDynInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetBarrierColor(barCol)));
		}
		MaterialDynInstance->SetScalarParameterValue(FName(TEXT("Intensity")), 10000.f);
		Diode3->SetVisibility(true, true);
		Diode3->SetMaterial(0, MaterialDynInstance);
	}
}

bool ALightningSwitch::OnInteract()
{
	/*When the player interacts with the switch it toggles all the controlled barriers to their other state*/
	//UE_LOG(LogDebug, Warning, TEXT("Interactible Lightning Switch"));
	for (auto Iter(m_vControledTerminals.CreateIterator()); Iter; Iter++)
	{
		if ((*Iter) != nullptr)
		{
			(*Iter)->ChangeActiveState();
		}
	}

	return true;
}
