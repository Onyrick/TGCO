

#include "TGCO.h"
#include "ElevatorsControler.h"


AElevatorsControler::AElevatorsControler(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void AElevatorsControler::PlayAnim()
{
	if ( CheckPlayersPresence() )
	{
		CloseFrontDoors();
		PlaySound();
		OpenBackDoors();
	}
}

bool AElevatorsControler::CheckPlayersPresence()
{
	for (TActorIterator<ATGCOCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ATGCOCharacter* Player = Cast<ATGCOCharacter>(*ActorItr);
		if (Player->IsInsideElevator() == false)
		{
			return false;
		}
	}
	return true;
}

void AElevatorsControler::CloseFrontDoors()
{
	FVector Offset = FVector(0.f, -200.f, 0.f);
	FuturElevator->GetFrontDoors()->SetWorldLocation(Offset);
	PastElevator->GetFrontDoors()->SetWorldLocation(Offset);
}

void AElevatorsControler::PlaySound()
{
	for (int i = 0; i < 10; ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("Your message"));
	}
	
}

void AElevatorsControler::OpenBackDoors()
{
	FVector Offset = FVector(0.f, 200.f, 0.f);
	FuturElevator->GetBackDoors()->SetWorldLocation(Offset);
	PastElevator->GetBackDoors()->SetWorldLocation(Offset);
}
