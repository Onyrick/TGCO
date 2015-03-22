
#include "TGCO.h"
#include "Monster.h"

AMonster::AMonster(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, fStunTime(1.f)
, fRespawnTime(1.f)
, bIsDead(false)
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
	if (GetAIController() != nullptr)
	{
		GetAIController()->StopMovement();
	}
	bIsDead = true;
}

bool AMonster::IsStun()
{
	return bIsStun;
}

void AMonster::Stun()
{
	bIsStun = true;
	GetWorldTimerManager().SetTimer(this, &AMonster::UnStun, fStunTime, false);

	if (GetAIController() != nullptr)
	{
		GetAIController()->StopMovement();
	}
}

void AMonster::UnStun()
{
	bIsStun = false;
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
	bIsDead = false;
}

bool AMonster::IsDead()
{
	return bIsDead;
}