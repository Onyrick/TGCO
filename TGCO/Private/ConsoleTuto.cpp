// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "ConsoleTuto.h"

AConsoleTuto::AConsoleTuto(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP)
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

void AConsoleTuto::OnInteract_Implementation()
{
	if (this.IsInteractive_Implementation())
	{
		//TODO
	}	
}

void AConsoleTuto::Highlight_Implementation(bool highlight)
{
	//TODO
}

bool AConsoleTuto::IsInteractive_Implementation()
{
	return bIsInteractive;
}

void AConsoleTuto::OnLookAt_Implementation()
{
	//TODO
}

void AConsoleTuto::SetInteractive_Implementation(bool _interactive)
{
	bIsInteractive = _interactive;
}

void AConsoleTuto::OnComponentBeginOverlap_Implementation()
{
	Highlight_Implementation(true);
}

void AConsoleTuto::OnComponentEndOverlap_Implementation()
{
	Highlight_Implementation(false);
}