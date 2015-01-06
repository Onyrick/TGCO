#include "TGCO.h"
#include "InteractiveElement.h"

AInteractiveElement::AInteractiveElement(const class FObjectInitializer& PCIP)
	: Super(PCIP), bIsInteractive(false), bCloseEnough(false)
{
	TriggerBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxTrigger_InteractiveElement"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveElement::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AInteractiveElement::OnOverlapEnd);

	StaticMesh = PCIP.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("StaticMesh_InteractiveElement"));

	TriggerBox->AttachParent = StaticMesh;

	RootComponent = StaticMesh;
}

void AInteractiveElement::OnInteract()
{
	unimplemented();
}

void AInteractiveElement::Highlight(bool highlight)
{
	//TODO
}

bool AInteractiveElement::IsInteractive()
{
	return bIsInteractive;
}

void AInteractiveElement::OnLookAt()
{
	Highlight(bCloseEnough);
}

void AInteractiveElement::OnLookAway()
{	
	Highlight(false);
}

void AInteractiveElement::SetInteractive(bool interactive)
{
	bIsInteractive = interactive;
}

void AInteractiveElement::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::White, TEXT("Begin Overlap"));
	}
	bCloseEnough = true;
}

void AInteractiveElement::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::White, TEXT("End Overlap"));
	}
	bCloseEnough = false;
}