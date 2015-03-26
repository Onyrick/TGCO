
#include "TGCO.h"
#include "SolutionType.h"
#include "SolutionGenerator.h"

ASolutionGenerator::ASolutionGenerator(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//SolutionType = ESolutionType::NONE;
	Player = nullptr;

	PointLight = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, "PointLight");
	PointLight->Intensity = 1000.f;
	PointLight->bVisible = true;
	
	PointLight->RegisterComponentWithWorld(GetWorld());
	PointLight->AttachTo(RootComponent);
	AddOwnedComponent(PointLight);

	FVector GeneratorPosition = GetActorLocation();
	PointLight->SetWorldLocation(FVector(GeneratorPosition.X, GeneratorPosition.Y, GeneratorPosition.Z + 30));
}

bool ASolutionGenerator::OnInteract()
{
	//TODO
	
	if (Player != nullptr)
	{
		Player->SetSolutionType(SolutionType);
		UE_LOG(LogTest, Warning, TEXT("Activate"));
	}
	return true;
}

void ASolutionGenerator::BeginPlay()
{
	Super::BeginPlay();
	UpdateColor();
}

void ASolutionGenerator::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	Player = Cast<ATGCOCharacter>(OtherActor);

}

void ASolutionGenerator::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OtherActor, OtherComp, OtherBodyIndex);
	Player = nullptr;
	
}

void ASolutionGenerator::UpdateColor()
{
	PointLight->SetLightColor(GetColorOfTheSolution(SolutionType));
}