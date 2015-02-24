
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
	AFan(const FObjectInitializer& ObjectInitializer);

	virtual void ReinitSpeed();

	UFUNCTION(BlueprintCallable, Category = Activation)
	void Activate(bool bActive);
	
	virtual void UpdateSpeed();

private:
	void Affect(float _fSpeed);

public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Force)
	URotatingMovementComponent* RotatingMovement;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Force)
	URadialForceComponent* RadialForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Member)
	AFan * FuturFan;

private:
	bool bIsActive;
};

