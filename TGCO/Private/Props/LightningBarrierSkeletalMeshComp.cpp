

#include "TGCO.h"
#include "Puzzle/BarrierColor.h"
#include "LightningBarrierSkeletalMeshComp.h"

ULightningBarrierSkeletalMeshComp::ULightningBarrierSkeletalMeshComp(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	/*Creation of the first pillar of the barrier mesh */
	pFirstTerminalComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("First Terminal Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> FirstTerminalShape(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	pFirstTerminalComponent->SetStaticMesh(FirstTerminalShape.Object);
	pFirstTerminalComponent->SetMobility(EComponentMobility::Movable);
	pFirstTerminalComponent->SetWorldLocation(FVector(0.f, 0.f, 0.0f));
	pFirstTerminalComponent->AttachTo(this);

	/*Creation of the second pillar of the barrier mesh */
	pSecondTerminalComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Second Terminal Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> SecondTerminalShape(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	pSecondTerminalComponent->SetStaticMesh(SecondTerminalShape.Object);
	pSecondTerminalComponent->SetMobility(EComponentMobility::Movable);
	pSecondTerminalComponent->SetWorldLocation(FVector(0.f, 500.f, 0.0f));
	pSecondTerminalComponent->AttachParent = pFirstTerminalComponent;

	/*Creation of the barrier part of the mesh */
	pLightningComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Lightning Barrier Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> LightningShape(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Trim.Shape_Trim'"));
	pLightningComponent->SetStaticMesh(LightningShape.Object);
	pLightningComponent->SetMobility(EComponentMobility::Movable);
	pLightningComponent->SetWorldRotation(FRotator(90, 0, 0));
	pLightningComponent->SetWorldScale3D(FVector(1.f, 5.f, 1.0f));
	pLightningComponent->SetWorldLocation(FVector(0, -250, 100));
	pLightningComponent->AttachParent = pSecondTerminalComponent;

//	SetBarrierMaterial(EColorBarrier::VE_Green);
}

void ULightningBarrierSkeletalMeshComp::ChangeLightningState(bool ActivateLightning)
{
	pLightningComponent->SetVisibility(ActivateLightning, false);
	auto collisionType = ActivateLightning ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision;
	pLightningComponent->SetCollisionEnabled(collisionType);
}

void ULightningBarrierSkeletalMeshComp::SetBarrierMaterial(EBarrierColor color)
{
	/*Retrieval of the pillars' material in order to apply them the given color */
	auto * MaterialInst1 = pFirstTerminalComponent->GetMaterial(0);
	UMaterialInstanceDynamic * MaterialInstanceFirstTerm = UMaterialInstanceDynamic::Create(MaterialInst1, this);

	auto * MaterialInst2 = pSecondTerminalComponent->GetMaterial(0);
	UMaterialInstanceDynamic * MaterialInstanceSecondTerm = UMaterialInstanceDynamic::Create(MaterialInst2, this);

	MaterialInstanceFirstTerm->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetBarrierColor(color)));
	MaterialInstanceFirstTerm->SetScalarParameterValue(FName(TEXT("Intensity")), 100.f);
	MaterialInstanceSecondTerm->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetBarrierColor(color)));
	MaterialInstanceSecondTerm->SetScalarParameterValue(FName(TEXT("Intensity")), 100.f);
	pFirstTerminalComponent->SetMaterial(0, MaterialInstanceFirstTerm);
	pSecondTerminalComponent->SetMaterial(0, MaterialInstanceSecondTerm);
}
