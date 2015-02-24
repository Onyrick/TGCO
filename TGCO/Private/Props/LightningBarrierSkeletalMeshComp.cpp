

#include "TGCO.h"
#include "LightningBarrierSkeletalMeshComp.h"

ULightningBarrierSkeletalMeshComp::ULightningBarrierSkeletalMeshComp(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	pFirstTerminalComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("First Terminal Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> FirstTerminalShape(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	pFirstTerminalComponent->SetStaticMesh(FirstTerminalShape.Object);
	pFirstTerminalComponent->SetMobility(EComponentMobility::Movable);
	pFirstTerminalComponent->SetWorldLocation(FVector(0.f, 0.f, 0.0f));
	pFirstTerminalComponent->AttachTo(this);

	pSecondTerminalComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Second Terminal Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> SecondTerminalShape(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	pSecondTerminalComponent->SetStaticMesh(SecondTerminalShape.Object);
	pSecondTerminalComponent->SetMobility(EComponentMobility::Movable);
	pSecondTerminalComponent->SetWorldLocation(FVector(0.f, 500.f, 0.0f));
	pSecondTerminalComponent->AttachParent = pFirstTerminalComponent;

	pLightningComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Lightning Barrier Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> LightningShape(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Trim.Shape_Trim'"));
	pLightningComponent->SetStaticMesh(LightningShape.Object);
	pLightningComponent->SetMobility(EComponentMobility::Movable);
	pLightningComponent->SetWorldRotation(FRotator(90, 0, 0));
	pLightningComponent->SetWorldScale3D(FVector(1.f, 5.f, 1.0f));
	pLightningComponent->SetWorldLocation(FVector(0, -250, 100));
	pLightningComponent->AttachParent = pSecondTerminalComponent;
}

void ULightningBarrierSkeletalMeshComp::ChangeLightningState(bool ActivateLightning)
{
	pLightningComponent->SetVisibility(ActivateLightning, false);
	auto collisionType = ActivateLightning ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision;
	pLightningComponent->SetCollisionEnabled(collisionType);
}
