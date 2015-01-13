// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "FixBot.h"

AFixBot::AFixBot(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	this->fStunTime = 3.f;
}

float AFixBot::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	//TODO
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	/*APlayer Player = Cast<APlayer>(DamageCauser);
	if (Player->IsPunching())
	{
		if (IsStun())
		{
			Destroy();
		}
	}
	if (Player->IsShooting())
	{
		Stun();
	}*/
	UE_LOG(LogDebug, Warning, TEXT("Take Damage FixBot"));

	return -1.f;
}
