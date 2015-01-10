// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "ConsoleTuto.h"

AConsoleTuto::AConsoleTuto(const class FObjectInitializer& PCIP) : Super(PCIP)
{

}

bool AConsoleTuto::IsUnlocked()
{
	return bIsUnlocked;
}

void AConsoleTuto::SetUnlocked(bool _unlock)
{
	bIsUnlocked = _unlock;
}

bool AConsoleTuto::OnInteract()
{
		//TODO
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("ACTIVATED CONSOLE"));
	}
	return true;
}