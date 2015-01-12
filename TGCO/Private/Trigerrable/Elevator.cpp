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
		//Change the bIsInsideElevator to True for the player which overlap the elevator.
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::White, TEXT("Open the front doors"));

		ATGCOCharacter* Player = Cast<ATGCOCharacter>(OtherActor);
		if (Player != NULL)
		{
			Player->SetInsideElevator();
			FString res = Player->IsInsideElevator() ? TEXT("Player is inside: true") : TEXT("Player is inside: false");
			GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::White, res);

			if (CheckPlayersPresence())
			{
				GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::White, TEXT("Cloose the front doors"));
			}
		}
		

	}
}

void AElevator::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//TODO: Close the back doors
	if (GEngine)
	{
		//Change the bIsInsideElevator to False for the player which overlap the elevator.
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::White, TEXT("Cloose the back doors"));

		ATGCOCharacter* Player = Cast<ATGCOCharacter>(OtherActor);
		if (Player != NULL)
		{
			Player->SetInsideElevator();
			FString res = Player->IsInsideElevator() ? TEXT("Player is inside: true") : TEXT("Player is inside: false");
			GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::White, res);
		}
	}
}

bool AElevator::CheckPlayersPresence()
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



