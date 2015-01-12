// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Elevator.h"


//AElevator
AElevator::AElevator(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	FrontDoors = PCIP.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("StaticMesh_FrontDoors"));
	BackDoors = PCIP.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("StaticMesh_BackDoors"));
}

void AElevator::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (GEngine)
	{
		//Change the bIsInsideElevator to True for the player which overlap the elevator.
		ATGCOCharacter* Player = Cast<ATGCOCharacter>(OtherActor);
		if (Player != NULL)
		{
			Player->SetInsideElevator();
			FString res = Player->IsInsideElevator() ? TEXT("Player is inside: true") : TEXT("Player is inside: false");
			GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::White, res);

			/*if (CheckPlayersPresence())
			{
				GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::White, TEXT("Cloose the front doors"));
			}*/
		}
		

	}
}

void AElevator::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//TODO: Close the back doors
	if (GEngine)
	{
		//Change the bIsInsideElevator to False for the player which overlap the elevator.
		ATGCOCharacter* Player = Cast<ATGCOCharacter>(OtherActor);
		if (Player != NULL)
		{
			Player->SetInsideElevator();
			FString res = Player->IsInsideElevator() ? TEXT("Player is inside: true") : TEXT("Player is inside: false");
			GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::White, res);
		}
	}
}

UStaticMeshComponent* AElevator::GetFrontDoors()
{
	return FrontDoors;
}

UStaticMeshComponent* AElevator::GetBackDoors()
{
	return BackDoors;
}