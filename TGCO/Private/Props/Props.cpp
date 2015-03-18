// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Props.h"
#include "Projectile.h"
#include "TGCOPlayerState.h"
#include "TGCOPlayerController.h"
#include "Net/UnrealNetwork.h"

AProps::AProps(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, fInitialSpeed(1000.f)
, fCurrentSpeed(1000.f)
{
	bReplicates = true;

	StaticMeshProps = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh_InteractiveElement"));
	
	RootComponent = StaticMeshProps;
}

UStaticMeshComponent* AProps::GetStaticMesh()
{
	return StaticMeshProps;
}

float AProps::TakeDamage(float fDamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	AProjectile* Projectile = Cast<AProjectile>(DamageCauser);

	if (Projectile == nullptr)
	{
		return -1.f;
	}

	ATGCOPlayerState * PS = Cast<ATGCOPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	PS->SetPropsAffected(this);

	EShootMode::Type ProjectileMode = Projectile->GetProjectileMode();
	PS->SetModUsed(ProjectileMode);

	float newSpeed = fCurrentSpeed;

	switch (ProjectileMode)
	{
	case EShootMode::STOP:
		newSpeed = 0;
		break;
	case EShootMode::SLOW:
		newSpeed = fInitialSpeed * 0.5;
		break;
	case EShootMode::SPEED:
		newSpeed = fInitialSpeed * 2;
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
		fCurrentSpeed = fNewSpeed;
		UpdateSpeedComponents();
	}
}

void AProps::ReinitSpeedToInitialSpeed()
{
	fCurrentSpeed = fInitialSpeed;
}

void AProps::OnRep_Speed()
{
	UpdateSpeedComponents();
}

void AProps::UpdateSpeedComponents()
{
	//unimplemented();
}

void AProps::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AProps, fCurrentSpeed);
}
