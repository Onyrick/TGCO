

#include "TGCO.h"
#include "RainbowBox.h"
#include "RainbowBoxHandlerFutur.h"

ARainbowBox::ARainbowBox(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer),
Color(ERainbowBoxColor::NONE),
bShouldNotify(false)
{
}

void ARainbowBox::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bShouldNotify)
	{
		for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			if (ActorItr->GetName().Contains("RainbowBoxHandlerFutur_BP"))
			{
				ARainbowBoxHandlerFutur* RainbowBoxHandlerFutur = Cast<ARainbowBoxHandlerFutur>(*ActorItr);
				RainbowBoxHandlerFutur->HideAllExcepted(Color);
			}
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

