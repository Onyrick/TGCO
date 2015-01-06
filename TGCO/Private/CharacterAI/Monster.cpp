// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Monster.h"

AMonster::AMonster(const class FObjectInitializer& PCIP) : Super(PCIP), fStunTime(1.f)
{
	AIControllerClass = AAIController::StaticClass();
}

float AMonster::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return -1.f;
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

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::White, TEXT("Stun : Stop MoveTo"));
	}
}

void AMonster::UnStun()
{
	bIsStun = false;
	// Resume MoveToLocation
	GetAIController()->ResumeMove(GetAIController()->GetCurrentMoveRequestID());

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::White, TEXT("UnStun : Resume MoveTo"));
	}
}

EPathFollowingRequestResult::Type AMonster::MoveToLocation(const FVector & Dest)//const FVector & Dest, float AcceptanceRadius, bool bStopOnOverlap, bool bUsePathfinding, bool bProjectDestinationToNavigation, bool bCanStrafe, TSubclassOf< class UNavigationQueryFilter > FilterClass)
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