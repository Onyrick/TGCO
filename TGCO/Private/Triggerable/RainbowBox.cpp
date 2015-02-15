

#include "TGCO.h"
#include "RainbowBox.h"
#include "RainbowBoxHandlerFutur.h"
#include "RainbowBoxHandlerPast.h"

ARainbowBox::ARainbowBox(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer),
Color(ERainbowBoxColor::NONE),
bShouldNotify(false),
bIsHideInPast(false)
{
}

void ARainbowBox::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ARainbowBoxHandlerFutur* RainbowBoxHandlerFutur = nullptr;
	ARainbowBoxHandlerPast* RainbowBoxHandlerPast = nullptr;

	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains("RainbowBoxHandlerFutur_BP"))
		{
			RainbowBoxHandlerFutur = Cast<ARainbowBoxHandlerFutur>(*ActorItr);
		}
		if (ActorItr->GetName().Contains("RainbowBoxHandlerPast_BP"))
		{
			RainbowBoxHandlerPast = Cast<ARainbowBoxHandlerPast>(*ActorItr);
		}
	}

	if (bShouldNotify)
	{
		if (RainbowBoxHandlerFutur != nullptr)
		{
			RainbowBoxHandlerFutur->HideAllOfThisColor(Color);
		}

		if (RainbowBoxHandlerPast != nullptr)
		{
			RainbowBoxHandlerPast->HideAllExcepted(this);
		}
	}
	else
	{
		if (RainbowBoxHandlerFutur)
		{
			RainbowBoxHandlerFutur->HideAllExcepted(this);
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

void ARainbowBox::SetColor(const ERainbowBoxColor::Color eColor)
{
	// Store color 
	Color = eColor;

	UMaterialInterface* MeshMat = StaticMesh->GetMaterial(0);
	MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MeshMat, this);
	MaterialInstanceDynamic->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(GetRedValueOfTheColor(eColor), GetGreenValueOfTheColor(eColor), GetBlueValueOfTheColor(eColor), 1.0));
	StaticMesh->SetMaterial(0, MaterialInstanceDynamic);
}

ERainbowBoxColor::Color ARainbowBox::GetColor()
{
	return Color;
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

