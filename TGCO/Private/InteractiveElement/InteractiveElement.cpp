
#include "TGCO.h"
#include "TGCOCharacter.h"
#include "InteractiveElement.h"

AInteractiveElement::AInteractiveElement(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, bIsInteractive(true)
, bCloseEnough(false)
{
	TriggerBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxTrigger_InteractiveElement"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveElement::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AInteractiveElement::OnOverlapEnd);

	StaticMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh_InteractiveElement"));

	TriggerBox->AttachTo(StaticMesh);
	RootComponent = StaticMesh;

	IsLookedAt = false;
	bCanExistsPastFuture = 0;

	
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

void AInteractiveElement::Highlight(bool highlight)
{
	auto name = this->GetClass()->GetName();

	//TODO : animation and visual effect
	if (highlight)
	{
		//UE_LOG(LogTest, Warning, TEXT("Highlight on"));
		IsLookedAt = true;
	}
	else
	{
		//UE_LOG(LogTest, Warning, TEXT("Highlight off"));
		IsLookedAt = false;
	}

}

bool AInteractiveElement::IsInteractive()
{
	//UE_LOG(LogDebug, Warning, TEXT("Check if element is interactible"));
	return bIsInteractive;
}

void AInteractiveElement::OnLookAt()
{
	Highlight(bCloseEnough);
}

void AInteractiveElement::SetInteractive(bool bInteractive)
{
	bIsInteractive = bInteractive;
}

void AInteractiveElement::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATGCOCharacter* PlayerCharacter = Cast<ATGCOCharacter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->IncreaseNumberOfCloseInteractiveElement();
		bCloseEnough = true;
	}
}

void AInteractiveElement::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATGCOCharacter* PlayerCharacter = Cast<ATGCOCharacter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->DecreaseNumberOfCloseInteractiveElement();
		bCloseEnough = false;
	}
}
