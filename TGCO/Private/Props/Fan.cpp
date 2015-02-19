

#include "TGCO.h"
#include "Fan.h"
#include "TGCOCharacter.h"

AFan::AFan(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	initialSpeed = 600; 
	speed = 600;
	RotatingMovement = ObjectInitializer.CreateDefaultSubobject<URotatingMovementComponent>(this, TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0, 0, initialSpeed);
	RotatingMovement->PivotTranslation = FVector(0, 0, 0);
	RotatingMovement->SetUpdatedComponent(StaticMeshProps);

	RadialForce = ObjectInitializer.CreateDefaultSubobject<URadialForceComponent>(this, TEXT("RadialForce_"));
	RadialForce->ForceStrength = initialSpeed * 1000;
	RadialForce->ImpulseStrength = 0;
	RadialForce->Radius = 800;
	RadialForce->Falloff = RIF_Linear;
	RadialForce->bImpulseVelChange = true;
	RadialForce->AttachParent = StaticMeshProps;
}


float AFan::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float returnValue = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	RotatingMovement->RotationRate = FRotator(0.f, 0.f, speed);
	if (RadialForce)
	{
		RadialForce->ForceStrength = speed * 1000;
		RadialForce->ImpulseStrength = speed * 0;
	}
	return returnValue;
}

void AFan::ReinitSpeed()
{
	speed = initialSpeed;

	RotatingMovement->RotationRate = FRotator(0.f, 0.f, speed);

	if (RadialForce)
	{
		RadialForce->ForceStrength = speed * 1000;
		RadialForce->ImpulseStrength = speed * 0;
	}
}
