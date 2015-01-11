// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Elevator.h"

AElevator::AElevator(const class FObjectInitializer& PCIP) : Super(PCIP)
{

}

void AElevator::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//TODO: Check if the second player is near the doors, then open the doors
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::White, TEXT("Begin Overlap Energy"));
		//Change the bIsInsideElevator to True for the player which overlap the elevator.
		for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ATGCOCharacter* Player = Cast<ATGCOCharacter>(*ActorItr);
			Player->SetInsideElevator();
			
		}
	}
}

void AElevator::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//TODO: Close the back doors
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::White, TEXT("End Overlap Energy"));
		//Change the bIsInsideElevator to False for the player which overlap the elevator.
		for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ATGCOCharacter* Player = Cast<ATGCOCharacter>(*ActorItr);
			Player->SetInsideElevator();

		}
	}
}

bool AElevator::CheckPlayersPresence()
{
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ATGCOCharacter* Player = Cast<ATGCOCharacter>(*ActorItr);
		if (Player->IsInsideElevator() == false)
		{
			return false;
		}
	}
	return true;
}



