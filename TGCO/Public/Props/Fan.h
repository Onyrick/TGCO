
#pragma once

#include "Props/Props.h"
#include "Fan.generated.h"

/**
 * TODO
 */
UCLASS()
class TGCO_API AFan : public AProps
{
	GENERATED_BODY()

public:
	/** Constructors */
	AFan(const FObjectInitializer& PCIP);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	virtual void ReinitSpeed();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Force)
	URotatingMovementComponent* RotatingMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Force)
	URadialForceComponent* RadialForce;
};