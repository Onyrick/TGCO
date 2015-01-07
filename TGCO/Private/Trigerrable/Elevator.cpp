// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Elevator.h"

AElevator::AElevator(const class FObjectInitializer& PCIP) : Super(PCIP)
{

}

void AElevator::OnComponentBeginOverlap()
{
	//TODO: Check if the second player is near the doors, then open the doors
}

void AElevator::OnComponentEndOverlap()
{
	//TODO: Close the door
}


