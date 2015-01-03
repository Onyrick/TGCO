// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "EnergyCell.h"

AEnergyCell::AEnergyCell(const class FObjectInitializer& PCIP) : Super(PCIP)
{

}

void AEnergyCell::OnComponentBeginOverlap()
{
	AddActorLocalOffset(FVector(0.f, 0.f, 1.f));
}

void AEnergyCell::OnComponentEndOverlap()
{
	
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