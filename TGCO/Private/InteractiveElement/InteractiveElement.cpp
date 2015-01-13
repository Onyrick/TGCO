#include "TGCO.h"
#include "TGCOCharacter.h"
#include "InteractiveElement.h"

AInteractiveElement::AInteractiveElement(const class FObjectInitializer& PCIP)
	: Super(PCIP), bIsInteractive(true), bCloseEnough(false)
{
	TriggerBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxTrigger_InteractiveElement"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveElement::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AInteractiveElement::OnOverlapEnd);

	StaticMesh = PCIP.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("StaticMesh_InteractiveElement"));
	
	TriggerBox->AttachTo(StaticMesh);
	RootComponent = StaticMesh;

	IsLookedAt = false;
	bCanExistsPastFuture = 0;
}

void AInteractiveElement::Highlight(bool highlight)
{
	auto name = this->GetClass()->GetName();

	//TODO
	if (highlight)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::White, name + TEXT(" : Je m'allume !!!"));
		}
		IsLookedAt = true;
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::White, name + TEXT(" : Je m'eteins !!!"));
		}
		IsLookedAt = false;
	}

}

bool AInteractiveElement::IsInteractive()
{
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("check if interactible"));		
	return bIsInteractive;
}

void AInteractiveElement::OnLookAt()
{
	Highlight(bCloseEnough);
}

void AInteractiveElement::SetInteractive(bool interactive)
{
	bIsInteractive = interactive;
}

void AInteractiveElement::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATGCOCharacter* PlayerCharacter = Cast<ATGCOCharacter>(OtherActor);

	if (PlayerCharacter != NULL)
	{
		PlayerCharacter->IncreaseNumberElement();
		bCloseEnough = true;
	}
}

void AInteractiveElement::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATGCOCharacter* PlayerCharacter = Cast<ATGCOCharacter>(OtherActor);

	if (PlayerCharacter != NULL)
	{
		PlayerCharacter->DecreaseNumberElement();
		bCloseEnough = false;
	}
}