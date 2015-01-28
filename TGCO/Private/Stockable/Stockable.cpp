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
	//PickStockableItem(this);
	ATGCOCharacter* PlayerCharacter = Cast<ATGCOCharacter>(OtherActor);

	if (PlayerCharacter != NULL)
	{
		PlayerCharacter->PickStockableItem(this);
		Destroy();
	}
}

void AStockable::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogDebug, Warning, TEXT("End Overlap Stockable"));
}

FString AStockable::GetDescription()
{
	return sDescription;
}

UTexture2D* AStockable::GetInventoryImageTexture()
{
	return InventoryImageTexture;
}