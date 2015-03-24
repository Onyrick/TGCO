
#include "TGCO.h"
#include "Fan.h"
#include "TGCOCharacter.h"
#include "TGCOPlayerController.h"

AFan::AFan(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, FutureFan(nullptr)
, bIsActive(true)
{
	bReplicates = true;

	// Initialize speed
	fInitialSpeed = 600; 
	fCurrentSpeed = 600;

	// Initialize component according to fInitialSpeed, can be override in BP
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
}

void AFan::UpdateSpeedComponents()
{
	RotatingMovement->RotationRate = FRotator(0.f, 0.f, fCurrentSpeed);
	if (RadialForce != nullptr)
	{
		RadialForce->ForceStrength = fCurrentSpeed * 1000;
		RadialForce->ImpulseStrength = fCurrentSpeed * 0;
	}

	if (FutureFan != nullptr)
	{
		FutureFan->AffectBySpeed(fCurrentSpeed);
	}
}

void AFan::AffectBySpeed(float _fSpeed)
{
	RotatingMovement->RotationRate = FRotator(0.f, 0.f, _fSpeed);
	if (RadialForce != nullptr)
	{
		RadialForce->ForceStrength = _fSpeed * 1000;
		RadialForce->ImpulseStrength = _fSpeed * 0;
	}

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		ATGCOPlayerController * PC = Cast<ATGCOPlayerController>(Iterator->Get());
		if (PC != nullptr)
		{
			PC->ClientAffectSpeedOnFutureFan(this, _fSpeed);
		}
	}
}

void AFan::ReinitSpeedToInitialSpeed()
{
	UpdateSpeedValue(fInitialSpeed);
}

void AFan::Activate(bool bActive)
{
	if (Role < ROLE_Authority)
	{
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			ATGCOPlayerController * PC = Cast<ATGCOPlayerController>(Iterator->Get());
			if (PC != nullptr)
			{
				PC->ServerActivateFan(this, bActive);
			}
		}
	}
	else
	{
		bIsActive = bActive;
		RotatingMovement->SetActive(bIsActive);

		if (FutureFan != nullptr)
		{
			FutureFan->bIsActive = bActive;
			FutureFan->RotatingMovement->SetActive(bIsActive);
		}
	}
}

void AFan::OnRep_Activate()
{
	RotatingMovement->SetActive(bIsActive);
}

void AFan::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AFan, RotatingMovement);
	DOREPLIFETIME(AFan, RadialForce);
	DOREPLIFETIME(AFan, bIsActive);
}
