

#include "TGCO.h"
#include "Capsule.h"

ACapsule::ACapsule(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{}

void ACapsule::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInterface* MeshMat = StaticMesh->GetMaterial(0);
	UMaterialInstanceDynamic *MatInstance = UMaterialInstanceDynamic::Create(MeshMat, this);
	MatInstance->SetVectorParameterValue(FName(TEXT("Color")), GetColorOfTheSolution(SolutionType));
	MatInstance->SetScalarParameterValue(FName(TEXT("Intensity")), 1.5);
	StaticMesh->SetMaterial(0, MatInstance);
}

TEnumAsByte<ESolutionType::Type> ACapsule::GetSolutionType()
{
	return SolutionType;
}

void ACapsule::UpdateIsCurrentlyUsed(bool bNewIsCurrentlyUsed)
{
	bIsCurrentlyUsed = bNewIsCurrentlyUsed;
}

bool ACapsule::IsCurrentlyUsed()
{
	return bIsCurrentlyUsed;
}
