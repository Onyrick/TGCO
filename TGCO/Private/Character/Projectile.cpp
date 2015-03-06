// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TGCOCharacter.h"
#include "Monster.h"
#include "Props.h"

AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, ProjectileMode(EShootMode::NONE)
, SolutionType(ESolutionType::NONE)
{
	// Use a sphere as a simple collision representation
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(10.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AProjectile::InitVelocity(const FVector& ShootDirection)
{
	if (ProjectileMovement)
	{
		// Set the projectile's velocity to the desired direction
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
	}
}

void AProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}

	//Stun the monster hit
	AMonster* Monster = Cast<AMonster>(OtherActor);
	if (Monster != nullptr)
	{
		FDamageEvent damage;
		Monster->TakeDamage(0.f, damage, Monster->GetController(), this);
	}

	AProps* Props = Cast<AProps>(OtherActor);
	if (Props != nullptr)
	{
		FDamageEvent damage;
		Props->TakeDamage(0.f, damage, nullptr, this);
	}

	Destroy();
}

ESolutionType::Type AProjectile::GetSolutionType()
{
	return SolutionType;
}

void AProjectile::SetSolutionType(ESolutionType::Type _solution)
{
	SolutionType = _solution;
}

void AProjectile::SetMode(EShootMode::Type _Mode)
{
	ProjectileMode = _Mode;
}

EShootMode::Type AProjectile::GetProjectileMode()
{
	return ProjectileMode;
}