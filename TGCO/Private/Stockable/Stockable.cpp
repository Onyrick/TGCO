// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOCharacter.h"
#include "Stockable.h"

AStockable::AStockable(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer),
sDescription("Stockable")
{
}

void AStockable::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogDebug, Warning, TEXT("Begin Overlap Stockable"));
	ATGCOCharacter* PlayerCharacter = Cast<ATGCOCharacter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->PickStockableItem(this);
		StaticMesh->DestroyComponent();
		TriggerBox->DestroyComponent();
	}
}

FString AStockable::GetDescription()
{
	return sDescription;
}

UTexture2D* AStockable::GetInventoryImageTexture()
{
	return InventoryImageTexture;
}