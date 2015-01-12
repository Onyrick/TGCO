// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOGameState.h"
#include "EnergyCell.h"

AEnergyCell::AEnergyCell(const class FObjectInitializer& PCIP) : Super(PCIP), iAmountOfEnergy(100)
{

}

void AEnergyCell::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::White, TEXT("Begin Overlap Energy"));
	}
	Consumed();
	Destroy();
}

void AEnergyCell::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::White, TEXT("End Overlap Energy"));
	}
}

void AEnergyCell::Consumed()
{
	AGameState * GameState = GetWorld()->GetGameState();
	ATGCOGameState* TGCOGameState = Cast<ATGCOGameState>(GameState);

	if (TGCOGameState != NULL)
	{
		TGCOGameState->AddEnergy(iAmountOfEnergy);
	}
}

int32 AEnergyCell::GetAmountOfEnergy()
{
	return iAmountOfEnergy;
}

void AEnergyCell::SetAmountOfEnergy(int32 _amount)
{
	iAmountOfEnergy = _amount;
}