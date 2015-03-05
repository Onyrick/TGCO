
#pragma once

#include "Props/Props.h"
#include "Fan.generated.h"

/**
 * This class defines a Fan that can be activate by Players. 
 * Once activate, Fan has a speed that can be change when it's take damage.
 * The Fan do some radial force on Players following it's speed.
 * It can also do some damage if Players go through.
 *
 * @TO DO : Deal damage in function not in BP
 */
UCLASS()
class TGCO_API AFan : public AProps
{
	GENERATED_BODY()

public:
	/** Constructors */
	AFan(const FObjectInitializer& ObjectInitializer);

	/** 
	 * Activate the Fan according to bActive 
	 * Set bIsActive parameter
	 * 
	 * @param	bActive		Whether the Fan must be active 
	 */
	UFUNCTION(BlueprintCallable, Category = Activation)
	void Activate(bool bActive);

	/** Function call when the Fan's bIsActive parameter is change by the server on the client */
	UFUNCTION()
	void OnRep_Activate();

	/** Reinitialize Fan's speed to the fInitialSpeed */
	virtual void ReinitSpeed();

	/** 
	 * Update Fan's rotating movement and radial force according to Fan's fCurrentSpeed 
	 * Also affect FutureFan parameter if not null. 
	 * @see AffectBySpeed
	 */
	virtual void UpdateSpeed();

private:
	/** 
	 * Affect the Fan's FutureFan parameter in UpdateSpeed if not null
	 * Update FutureFan's rotating movement and radial force according to Fan's fCurrentSpeed 
	 * 
	 * @param	_fSpeed		The Fan's currentSpeed, not FutureFan's currentSpeed.
	 */
	void AffectBySpeed(float _fSpeed);

public:
	/** A RotatingMovementComponent that is in charge of Fan's rotation */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Force)
	URotatingMovementComponent* RotatingMovement;
	/** A RadialForceComponent that is in charge of Fan's force on Players  */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Force)
	URadialForceComponent* RadialForce;
	/** If this Fan has an equivalent in Future, set it to be affected by changing on this Fan */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Member)
	AFan * FutureFan;

private:
	/** Whether the Fan is active, default is true */
	UPROPERTY(ReplicatedUsing = OnRep_Activate)
	bool bIsActive;
};

