// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

#define COLLISION_PROJECTILE    ECC_GameTraceChannel1

/**
 * Define the Projectile launch by the Player 
 */
UCLASS()
class TGCO_API AProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:
	AProjectile(const FObjectInitializer& ObjectInitializer);

	/** Inits velocity of the projectile in the shoot direction */
	void InitVelocity(const FVector& ShootDirection);

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	ESolutionType::Type GetSolutionType();

	void SetSolutionType(ESolutionType::Type _solution);

protected:
	TEnumAsByte<ESolutionType::Type> SolutionType;
};
