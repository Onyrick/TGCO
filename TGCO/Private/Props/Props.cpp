// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Props.h"
#include "Projectile.h"
#include "TGCOPlayerState.h"

AProps::AProps(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	StaticMeshProps = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh_InteractiveElement"));
	
	RootComponent = StaticMeshProps;
	initialSpeed = 1000.f;
	speed = 1000.f;
}

UStaticMeshComponent* AProps::getStaticMesh()
{
	return StaticMeshProps;
}

float AProps::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	AProjectile* Projectile = Cast<AProjectile>(DamageCauser);

	if (Projectile == NULL)
	{
		return -1.f;
	}

	ATGCOPlayerState * PS = Cast<ATGCOPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	PS->SetPropsAffected(this);

	FString ProjectileMode = Projectile->GetProjectileMode();

	if (ProjectileMode.Equals(TEXT("STOP"), ESearchCase::IgnoreCase))
	{
		speed = 0;
	}
	else if (ProjectileMode.Equals(TEXT("SLOW"), ESearchCase::IgnoreCase))
	{
		speed = speed * 0.5;
	}
	else if (ProjectileMode.Equals(TEXT("SPEED"), ESearchCase::IgnoreCase))
	{
		speed = speed * 2;
	}

	UE_LOG(LogDebug, Warning, TEXT("Hit by projectile %s, now speed : %f"), *ProjectileMode, speed);

	return -1.f;
}

void AProps::ReinitSpeed()
{
	speed = initialSpeed;
}
