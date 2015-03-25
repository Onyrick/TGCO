
#include "TGCO.h"
#include "Monster.h"

AMonster::AMonster(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, fStunTime(1.f)
, fRespawnTime(1.f)
, bIsDead(false)
, bReadyToMove(false)
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
	if (Role < ROLE_Authority)
	{
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerStunMonster(this);
		}
	}
	else
	{
		bIsStun = true;
		GetWorldTimerManager().SetTimer(this, &AMonster::UnStun, fStunTime, false);

		if (GetAIController() != nullptr)
		{
			GetAIController()->StopMovement();
		}
	}
}

void AMonster::UnStun()
{
	bIsStun = false;
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
	if (Role < ROLE_Authority)
	{
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerRespawnMonster(this);
		}
	}
	else
	{
		Super::RespawnAI();
		bIsDead = false;
	}
}

bool AMonster::IsDead()
{
	return bIsDead;
}

bool AMonster::isReadyToMove()
{
	return bReadyToMove;
}

void AMonster::SetReadyToMove(bool _ready)
{
	if (Role < ROLE_Authority)
	{
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerSetReadyToMove(this, _ready);
		}
	}
	else
	{
		bReadyToMove = _ready;
		RespawnAI();
	}
}

void AMonster::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AMonster, bReadyToMove);
}