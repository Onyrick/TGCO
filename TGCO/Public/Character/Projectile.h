
#pragma once

#include "GameFramework/Actor.h"
#include "SolutionType.h"
#include "Projectile.generated.h"

#define COLLISION_PROJECTILE    ECC_GameTraceChannel1

/**
 * @brief	Define the Projectile launch by the Player.
 * 			Projectile is spawn with an initial speed and have a ProjectileMode.
 */
UCLASS()
class TGCO_API AProjectile : public AActor
{
	GENERATED_BODY()

public:

	/** @brief	A sphere component*. */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;

	/** @brief	A projectile movement component*. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	/** @brief A projectile static mesh component*. */
	UPROPERTY(EditAnywhere, Category = "Projectile Static Mesh")
	class UStaticMeshComponent* MeshProjectile;

public:

	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	AProjectile(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief	Initialises the velocity in the shoot direction.
	 *
	 * @param	ShootDirection	The shoot direction.
	 */
	void InitVelocity(const FVector& ShootDirection);

	/**
	 * @brief	Executes the hit action.
	 * 			Call when projectile hits something.
	 *
	 * @param 	OtherActor	If non-null, the other actor hit.
	 * @param 	OtherComp 	If non-null, the other component hit.
	 * @param	NormalImpulse	  	The normal impulse.
	 * @param	Hit				  	The hit structure.
	 */
	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** @brief	return sphere collision component*. */
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** @brief  return projectile movement subobject*. */
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	/**
	 * @brief	Sets a mode.
	 *
	 * @param	_Mode	The mode (speed, stop, slow).
	 */
	void SetMode(EShootMode::Type _Mode);

	/**********************************************************************************************//**
	 * @brief	Sets particle system.
	 *
	 * @param	_Mode	The mode.
	 **************************************************************************************************/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SetMode")
	void SetParticleSystem(EShootMode::Type _Mode);

	/**
	 * @brief	Gets projectile mode.
	 *
	 * @return	The projectile mode.
	 */
	UFUNCTION(BlueprintCallable, Category = "ShootMode")
	EShootMode::Type GetProjectileMode();

	/**
	 * @brief	Sets solution type.
	 *
	 * @param	_solution	The solution.
	 */
	void SetSolutionType(ESolutionType::Type _solution);

	/**
	 * @brief	Gets solution type.
	 *
	 * @return	The solution type.
	 */
	ESolutionType::Type GetSolutionType();

protected:

	/** @brief	The projectile mode (speed, stop, slow) */
	EShootMode::Type ProjectileMode;

	/** @brief	Type of the solution that affect monsters. */
	TEnumAsByte<ESolutionType::Type> SolutionType;

	/** Projectile Material */
	UMaterialInstanceDynamic *MaterialInstance;

};
