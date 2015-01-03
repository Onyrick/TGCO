// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Monster.h"

AMonster::AMonster(const class FObjectInitializer& PCIP) : Super(PCIP)
{

}

AAIController* AMonster::GetAIController()
{
	//TODO
	return NULL;
}

void AMonster::Destroy()
{
	//TODO
}

float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	//TODO
	return -1.f;
}

void AMonster::ReceiveActorBeginOverlapAI(AActor* OtherActor)
{
	//TODO
	//Super::ReceiveActorBeginOverlap(OtherActor);
}

bool AMonster::IsStun()
{
	return bIsStun;
}

void AMonster::Stun(bool _stun)
{
	bIsStun = _stun;
	//TODO
}

EPathFollowingRequestResult::Type AMonster::MoveToLocation(const FVector & Dest, float AcceptanceRadius, bool bStopOnOverlap, bool bUsePathfinding, bool bProjectDestinationToNavigation, bool bCanStrafe, TSubclassOf< class UNavigationQueryFilter > FilterClass)
{
	//TODO
	return EPathFollowingRequestResult::Failed;
}

void AMonster::PlayMoveSound()
{
	//TODO
}

void AMonster::PlayMoveAnimation()
{
	//TODO
}