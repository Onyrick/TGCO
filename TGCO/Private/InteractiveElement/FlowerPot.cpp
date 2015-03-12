// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "FlowerPot.h"
#include <ConstructorHelpers.h>
#include "Props/Lever.h"


AFlowerPot::AFlowerPot(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bIsInteractive = false;
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> PotShape(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	StaticMesh->SetStaticMesh(PotShape.Object);
	TreeTrunc = ObjectInitializer.CreateDefaultSubobject<UTree>(this, TEXT("TreeTrunc"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> TreeShape(TEXT("StaticMesh'/Game/StarterContent/Props/SM_PillarFrame300.SM_PillarFrame300'"));
	TreeTrunc->SetStaticMesh(TreeShape.Object);
	TreeTrunc->AttachTo(StaticMesh);
	TreeTrunc->SetVisibility(false, true);

	TreeCapsuleOverlapCheck = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("TreeBoxOverlapCheck"));
	TreeCapsuleOverlapCheck->AttachTo(StaticMesh);
}


bool AFlowerPot::OnInteract()
{
	//TODO
	UE_LOG(LogDebug, Warning, TEXT("Interactible flower pot"));

	AFlowerPot* FutureSelf = Cast<AFlowerPot>(FutureElement);
	if (FutureSelf != nullptr)
	{
		FutureSelf->GrowTree();
	}

	return true;
}

//TODO Comment
void AFlowerPot::GrowTree()
{
	if (TreeTrunc != nullptr)
	{
		TreeTrunc->SetVisibility(true, true);
		TreeVisible.Broadcast();
		TArray<AActor*> OutOverlappingComponents;
		this->GetOverlappingActors(OutOverlappingComponents);
		for (int i = 0; i < OutOverlappingComponents.Num(); i++)
		{
			auto component = OutOverlappingComponents[i];
			auto classname = component->GetClass()->GetName();
			if (classname.Contains(TEXT("Lever")))
			{
				auto tempLever = Cast<ALever>(component);
				tempLever->getStaticMesh()->SetVisibility(false);

				UE_LOG(LogDebug, Warning, TEXT("Tree has pushed the lever"));
			}			
		}

	}
}

void AFlowerPot::PlantSeed(ASeed * Seed)
{
	PlantedSeed = Seed;
}

ASeed * AFlowerPot::RemoveSeed()
{
	ASeed *RetSeed = PlantedSeed;
	PlantedSeed = nullptr;
	return RetSeed;
}

ASeed * AFlowerPot::SwapSeed(ASeed * Seed)
{
	ASeed *RetSeed = PlantedSeed;
	PlantedSeed = Seed;
	return RetSeed;
}
