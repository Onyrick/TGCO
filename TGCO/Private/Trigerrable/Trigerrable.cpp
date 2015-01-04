#include "TGCO.h"
#include "Trigerrable.h"

ATrigerrable::ATrigerrable(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	
	TriggerBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxTrigger_Trigerrable"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATrigerrable::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATrigerrable::OnOverlapEnd);	

	StaticMesh = PCIP.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("StaticMesh_Trigerrable"));

	TriggerBox->AttachParent = StaticMesh;

	RootComponent = StaticMesh;
}

void ATrigerrable::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	unimplemented();
}

void ATrigerrable::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	unimplemented();
}