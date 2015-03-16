// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Seed.h"


ASeed::ASeed(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> SeedShape(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	StaticMesh->SetStaticMesh(SeedShape.Object);
}

bool ASeed::OnInteract()
{
	SeedPicked.Broadcast();
	//UE_LOG(LogDebug, Warning, TEXT("Interactible seed"));
	return true;
}
