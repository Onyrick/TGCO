// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SolutionType.h"
#include "Projectile.generated.h"

#define COLLISION_PROJECTILE    ECC_GameTraceChannel1

/**
 * Define the Projectile launch by the Player.
 * Projectile is spawn with an initial speed and have a ProjectileMode
 */
UCLASS()

class TGCO_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	/** Projectile Mesh */
	UPROPERTY(EditAnywhere, Category = "Projectile Static Mesh")
	class UStaticMeshComponent* MeshProjectile;

public:
	/** Constructors */
	AProjectile(const FObjectInitializer& ObjectInitializer);

	/** Initialize velocity of the projectile in the shoot direction */
	void InitVelocity(const FVector& ShootDirection);

	/** Function called when projectile hits something */
	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	/** Set Projectile's mode (speed, stop, slow) */
	void SetMode(EShootMode::Type _Mode);
	/** Get Projectile's mode (speed, stop, slow) */
	EShootMode::Type GetProjectileMode();

	/** Set Projectile's solution type */
	void SetSolutionType(ESolutionType::Type _solution);
	/** Get Projectile's solution type */
	ESolutionType::Type GetSolutionType();

protected:
	/** Projectile Mode (speed, stop, slow) */
	EShootMode::Type ProjectileMode;
	
	/** Projectile SolutionType that affect Monster */
	TEnumAsByte<ESolutionType::Type> SolutionType;

	/** Projectile Material */
	UMaterialInstanceDynamic *MaterialInstance;
	
};
