// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Props.h"
#include "Projectile.h"
#include "TGCOPlayerState.h"
#include "TGCOPlayerController.h"
#include "Net/UnrealNetwork.h"

AProps::AProps(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bReplicates = true;

	StaticMeshProps = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh_InteractiveElement"));
	
	RootComponent = StaticMeshProps;
	fInitialSpeed = 1000.f;
	fSpeed = 1000.f;
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
	// TODO Check that
	ATGCOPlayerState * PS = Cast<ATGCOPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	PS->SetPropsAffected(this);

	EShootMode::Type ProjectileMode = Projectile->GetProjectileMode();
	PS->SetModUsed(ProjectileMode);

	float newSpeed = fSpeed;

	switch (ProjectileMode)
	{
	case EShootMode::STOP:
		newSpeed = 0;
		break;
	case EShootMode::SLOW:
		newSpeed = fSpeed * 0.5;
		break;
	case EShootMode::SPEED:
		newSpeed = fSpeed * 2;
		break;
	default:
		break;
	}

	UpdateSpeedValue(newSpeed);

	return -1.f;
}

void AProps::UpdateSpeedValue(float fNewSpeed)
{
	if (Role < ROLE_Authority)
	{
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerUpdateSpeedValueOnProps(this, fNewSpeed);
		}
	}
	else
	{
		fSpeed = fNewSpeed;
		UpdateSpeed();
	}
}

void AProps::ReinitSpeed()
{
	fSpeed = fInitialSpeed;
}

void AProps::OnRep_Speed()
{
	UpdateSpeed();
}

void AProps::UpdateSpeed()
{
	unimplemented();
}

void AProps::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AProps, fSpeed);
}
