// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Monster.h"

AMonster::AMonster(const class FObjectInitializer& PCIP)
: Super(PCIP)
, fStunTime(1.f)
, fRespawnTime(1.f)
{
	GetCharacterMovement()->MaxWalkSpeed = 100.f;
}

float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return -1.f;
}

void AMonster::Destroyed()
{
	Super::Destroyed();
	GetAIController()->PauseMove(GetAIController()->GetCurrentMoveRequestID());
}

bool AMonster::IsStun()
{
	return bIsStun;
}

void AMonster::Stun()
{
	bIsStun = true;
	GetWorldTimerManager().SetTimer(this, &AMonster::UnStun, fStunTime, false);

	// Stop MoveToLocation
	GetAIController()->PauseMove(GetAIController()->GetCurrentMoveRequestID());

	UE_LOG(LogDebug, Warning, TEXT("Stun Monster"));
}

void AMonster::UnStun()
{
	bIsStun = false;
	// Resume MoveToLocation
	GetAIController()->ResumeMove(GetAIController()->GetCurrentMoveRequestID());
}

EPathFollowingRequestResult::Type AMonster::MoveToLocation(const FVector & Dest)
{
	return GetAIController()->MoveToLocation(Dest);
}

void AMonster::PlayMoveSound()
{
	//TODO
}

void AMonster::PlayMoveAnimation()
{
	//TODO
}

float AMonster::GetWalkSpeed()
{
	return GetCharacterMovement()->MaxWalkSpeed;
}

void AMonster::SetWalkSpeed(float _speed)
{
	GetCharacterMovement()->MaxWalkSpeed = _speed;
}

void AMonster::RespawnAI()
{
	Super::RespawnAI();
	GetAIController()->ResumeMove(GetAIController()->GetCurrentMoveRequestID());
}