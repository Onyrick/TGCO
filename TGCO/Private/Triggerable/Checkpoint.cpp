
#include "TGCO.h"
#include "Checkpoint.h"
#include "TGCOCharacter.h"

ACheckpoint::ACheckpoint(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{}

void ACheckpoint::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogDebug, Warning, TEXT("Begin Overlap Checkpoint"));
	
	ATGCOCharacter* Character = Cast<ATGCOCharacter>(OtherActor);
	if (Character)
	{
		Character->SetCheckpoint();
	}
}

void ACheckpoint::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogDebug, Warning, TEXT("End Overlap Checkpoint"));
}
