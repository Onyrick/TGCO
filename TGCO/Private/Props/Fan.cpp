
#include "TGCO.h"
#include "Fan.h"
#include "TGCOCharacter.h"
#include "TGCOPlayerController.h"

AFan::AFan(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	fInitialSpeed = 600; 
	fSpeed = 600;
	RotatingMovement = ObjectInitializer.CreateDefaultSubobject<URotatingMovementComponent>(this, TEXT("RotatingMovement"));
	RotatingMovement->RotationRate = FRotator(0, 0, fInitialSpeed);
	RotatingMovement->PivotTranslation = FVector(0, 0, 0);
	RotatingMovement->SetUpdatedComponent(StaticMeshProps);

	RadialForce = ObjectInitializer.CreateDefaultSubobject<URadialForceComponent>(this, TEXT("RadialForce_"));
	RadialForce->ForceStrength = fInitialSpeed * 1000;
	RadialForce->ImpulseStrength = 0;
	RadialForce->Radius = 800;
	RadialForce->Falloff = RIF_Linear;
	RadialForce->bImpulseVelChange = true;
	RadialForce->AttachParent = StaticMeshProps;

	bIsActive = true;

	FuturFan = NULL;
}

void AFan::UpdateSpeed()
{
	RotatingMovement->RotationRate = FRotator(0.f, 0.f, fSpeed);
	if (RadialForce)
	{
		RadialForce->ForceStrength = fSpeed * 1000;
		RadialForce->ImpulseStrength = fSpeed * 0;
	}

	if (FuturFan)
	{
		FuturFan->Affect(fSpeed);
	}
}

void AFan::Affect(float _fSpeed)
{
	RotatingMovement->RotationRate = FRotator(0.f, 0.f, _fSpeed);
	if (RadialForce)
	{
		RadialForce->ForceStrength = _fSpeed * 1000;
		RadialForce->ImpulseStrength = _fSpeed * 0;
	}

	ATGCOPlayerController * PC;
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		PC = Cast<ATGCOPlayerController>(Iterator->Get());
		PC->ClientAffectSpeedOnFuturFan(this, _fSpeed);
	}
}

void AFan::ReinitSpeed()
{
	UpdateSpeedValue(fInitialSpeed);
}

void AFan::Activate(bool bActive)
{
	bIsActive = bActive;
	RotatingMovement->SetActive(bIsActive);
	if (!bIsActive)
	{
		UpdateSpeedValue(0);
	}
	else
	{
		ReinitSpeed();
	}

	if (FuturFan)
	{
		FuturFan->Activate(bActive);
	}
}

void AFan::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AFan, RotatingMovement);
	DOREPLIFETIME(AFan, RadialForce);
}
