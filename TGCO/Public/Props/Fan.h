
#pragma once

#include "Props/Props.h"
#include "Fan.generated.h"

/**
 * @brief	This class defines a Fan that can be activate by Players. Once activate, Fan has a
 * 			speed that can be change when it's take damage. The Fan do some radial force on
 * 			Players following it's speed. It can also do some damage if Players go through.
 * 			
 * 			TODO : Deal damage in function not in BP.
 */
UCLASS()
class TGCO_API AFan : public AProps
{
	GENERATED_BODY()

public:

	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	AFan(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief	Activate the Fan according to bActive 
	 * 			Set bIsActive parameter.
	 *
	 * @param	bActive	Whether the Fan must be active.
	 */
	UFUNCTION(BlueprintCallable, Category = Activation)
	void Activate(bool bActive);
	
	/**
	 * @brief	Executes the rep activate action. 
	 * 			Function call when the Fan's bIsActive parameter is
	 * 			change by the server on the client.
	 */
	UFUNCTION()
	void OnRep_Activate();

	/** @brief	Reinitializes the speed to the fInitialSpeed. */
	virtual void ReinitSpeed();

	/**
	 * @brief	Update Fan's rotating movement and radial force according to Fan's fCurrentSpeed 
	 * 			Also affect FutureFan parameter if not null.
	 *
	 * @see	AffectBySpeed
	 */
	virtual void UpdateSpeed();

private:

	/**
	 * @brief	Affect the Fan's FutureFan parameter in UpdateSpeed if not null Update FutureFan's
	 * 			rotating movement and radial force according to Fan's fCurrentSpeed.
	 *
	 * @param	_fSpeed	The Fan's currentSpeed, not FutureFan's currentSpeed.
	 */
	void AffectBySpeed(float _fSpeed);

public:

	/** @brief	A RotatingMovementComponent that is in charge of Fan's rotation. */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Force)
	URotatingMovementComponent* RotatingMovement;

	/** @brief	A RadialForceComponent that is in charge of Fan's force on Players. */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Force)
	URadialForceComponent* RadialForce;

	/**
	 * @brief	The future fan.
	 * 			If this Fan has an equivalent in Future, set it to be affected by changing on this Fan.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Member)
	AFan * FutureFan;

private:

	/** @brief	true if this object is active. */
	UPROPERTY(ReplicatedUsing = OnRep_Activate)
	bool bIsActive;
};
