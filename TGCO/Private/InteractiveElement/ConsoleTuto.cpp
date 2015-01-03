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

void AConsoleTuto::OnInteract()
{
		//TODO
}

void AConsoleTuto::Highlight(bool highlight)
{
	//TODO

}

bool AConsoleTuto::IsInteractive()
{
	return bIsInteractive;
}

void AConsoleTuto::OnLookAt()
{
	//TODO
	AddActorLocalOffset(FVector(0.f, 0.f, 1.f));
}

void AConsoleTuto::SetInteractive(bool _interactive)
{
	bIsInteractive = _interactive;
}

void AConsoleTuto::OnComponentBeginOverlap()
{
	Highlight(true);
}

void AConsoleTuto::OnComponentEndOverlap()
{
	Highlight(false);
}