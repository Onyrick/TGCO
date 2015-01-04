// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "EnergyCell.h"

AEnergyCell::AEnergyCell(const class FObjectInitializer& PCIP) : Super(PCIP)
{

}

void AEnergyCell::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AddActorLocalOffset(FVector(0.f, 0.f, 5.f));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::White, TEXT("Begin Overlap Energy"));
	}
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

}

int32 AEnergyCell::GetAmountOfEnergy()
{
	return iAmountOfEnergy;
}

void AEnergyCell::SetAmountOfEnergy(int32 _amount)
{
	iAmountOfEnergy = _amount;
}