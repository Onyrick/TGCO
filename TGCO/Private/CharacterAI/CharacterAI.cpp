// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "ControllerAI.h"
#include "CharacterAI.h"

ACharacterAI::ACharacterAI(const class FObjectInitializer& PCIP) 
	: Super(PCIP)
{
	StaticMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh_CharacterAI"));
	StaticMesh->bGenerateOverlapEvents = true;
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	AIControllerClass = AControllerAI::StaticClass();
	
	GetMesh()->AttachTo(StaticMesh);
	StaticMesh->AttachTo(GetCapsuleComponent());

	RootComponent = GetCapsuleComponent();

}

AControllerAI* ACharacterAI::GetAIController()
{
	return Cast<AControllerAI>(GetController());
}

void ACharacterAI::Destroy()
{
	//TODO
	Super::Destroy();
	StaticMesh->DestroyComponent();
}

float ACharacterAI::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return -1.f;
}

void ACharacterAI::ReceiveActorBeginOverlap(AActor* OtherActor)
{
	//TODO
	UE_LOG(LogTest, Warning, TEXT("Receive Actor Begin Overlap"));
}

void ACharacterAI::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRotation, DeltaTime);
}

