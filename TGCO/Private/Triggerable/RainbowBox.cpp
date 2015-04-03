
#include "TGCO.h"
#include "Net/UnrealNetwork.h"
#include "RainbowBox.h"
#include "RainbowBoxHandlerFuture.h"
#include "RainbowBoxHandlerPast.h"

ARainbowBox::ARainbowBox(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, iColor(0)
, bShouldNotify(false)
, bIsHideInPast(false)
{
	bReplicates = true;
	MaterialInstanceDynamic = nullptr;
}

void ARainbowBox::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ARainbowBoxHandlerFuture* RainbowBoxHandlerFuture = nullptr;
	ARainbowBoxHandlerPast* RainbowBoxHandlerPast = nullptr;

	// Get RainbowBoxHandler of the future and of the past
	for (TActorIterator<ARainbowBoxHandlerFuture> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains("RainbowBoxHandlerFuture_BP"))
		{
			RainbowBoxHandlerFuture = Cast<ARainbowBoxHandlerFuture>(*ActorItr);
		}
	}

	for (TActorIterator<ARainbowBoxHandlerPast> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains("RainbowBoxHandlerPast_BP"))
		{
			RainbowBoxHandlerPast = Cast<ARainbowBoxHandlerPast>(*ActorItr);
		}
	}

	// If the rainbowBox have to notify RainbowBoxHandler of the future
	if (bShouldNotify)
	{
		if (RainbowBoxHandlerFuture != nullptr)
		{
			RainbowBoxHandlerFuture->HideAllOfThisColor(GetColorFromInt(iColor));
		}

		if (RainbowBoxHandlerPast != nullptr)
		{
			RainbowBoxHandlerPast->HideAllExcepted(this);
		}
	}
	else
	{
		if (RainbowBoxHandlerFuture)
		{
			RainbowBoxHandlerFuture->HideAllExcepted(this);
		}
	}
}

void ARainbowBox::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ARainbowBox::Hide()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ARainbowBox::Show()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void ARainbowBox::SetColor(const ERainbowBoxColor::Color eNewColor)
{
	// Store color 
	iColor = GetIntFromColor(eNewColor);

	UMaterialInterface* MeshMat = StaticMesh->GetMaterial(0);
	MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MeshMat, this);
	MaterialInstanceDynamic->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetRedValueOfTheColor(eNewColor), GetGreenValueOfTheColor(eNewColor), GetBlueValueOfTheColor(eNewColor), 1.0));
	StaticMesh->SetMaterial(0, MaterialInstanceDynamic);
}

void ARainbowBox::OnRep_Material()
{
	ERainbowBoxColor::Color eColor = GetColorFromInt(iColor);
	UMaterialInterface* MeshMat = StaticMesh->GetMaterial(0);
	MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MeshMat, this);
	MaterialInstanceDynamic->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetRedValueOfTheColor(eColor), GetGreenValueOfTheColor(eColor), GetBlueValueOfTheColor(eColor), 1.0));
	StaticMesh->SetMaterial(0, MaterialInstanceDynamic);
}

ERainbowBoxColor::Color ARainbowBox::GetColor()
{
	return GetColorFromInt(iColor);
}

void ARainbowBox::SetShouldNotify(bool bNewShouldNotify)
{
	bShouldNotify = bNewShouldNotify;
}

void ARainbowBox::SetIsHideInPast(bool bNewIsHideInPast)
{
	bIsHideInPast = bNewIsHideInPast;
}

bool ARainbowBox::GetIsHideInPast()
{
	return bIsHideInPast;
}

void ARainbowBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(ARainbowBox, iColor);
}
