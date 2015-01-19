// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Triggerable.h"

ATriggerable::ATriggerable(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{	
	TriggerBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxTrigger_Trigerrable"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATriggerable::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATriggerable::OnOverlapEnd);	

	StaticMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh_Trigerrable"));

	TriggerBox->AttachParent = StaticMesh;

	RootComponent = StaticMesh;
}

void ATriggerable::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	unimplemented();
}

void ATriggerable::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	unimplemented();
}
