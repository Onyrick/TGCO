// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOGameState.h"
#include "Engine.h"
#include "EnergyCell.h"

AEnergyCell::AEnergyCell(const class FObjectInitializer& PCIP) 
: Super(PCIP)
, iAmountOfEnergy(100)
{}

void AEnergyCell::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Consumed();
	UE_LOG(LogDebug, Warning, TEXT("Begin Overlap Energy"));
}

void AEnergyCell::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogDebug, Warning, TEXT("End Overlap Energy"));
}

void AEnergyCell::Consumed()
{
	ATGCOGameState* gameState = Cast<ATGCOGameState>(GetWorld()->GetGameState());
	if (gameState)
	{
		gameState->AddEnergy(iAmountOfEnergy);
	}
	Destroy();
}

int32 AEnergyCell::GetAmountOfEnergy()
{
	return iAmountOfEnergy;
}

void AEnergyCell::SetAmountOfEnergy(int32 _amount)
{
	iAmountOfEnergy = _amount;
}
