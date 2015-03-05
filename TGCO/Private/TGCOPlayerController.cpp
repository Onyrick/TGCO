

#include "TGCO.h"
#include "TGCOPlayerController.h"
#include "TGCOGameInstance.h"
#include "GameFramework/PlayerInput.h"
#include "Props.h"
#include "Fan.h"

ATGCOPlayerController::ATGCOPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bShouldPerformFullTickWhenPaused = true;
}

void ATGCOPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// UI input
	InputComponent->BindAction("PutGameInPause", IE_Pressed, this, &ATGCOPlayerController::OnTogglePause);
}

void ATGCOPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATGCOPlayerController::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);
	if (IsPaused())
	{
		if (PlayerInput != NULL)
		{
			//Tick the Input handler
			PlayerInput->Tick(DeltaTime);

			//Process inputs
			ProcessPlayerInput(DeltaTime, false);
		}
	}
}

void ATGCOPlayerController::OnTogglePause()
{
	UE_LOG(LogOnline, Log, TEXT("Call OnTogglePause"));
}

bool ATGCOPlayerController::SetPause(bool bPause, FCanUnpause CanUnpauseDelegate /*= FCanUnpause()*/)
{
	UE_LOG(LogOnline, Log, TEXT("Call SetPause"));
	SetIgnoreMoveInput(bPause);
	SetIgnoreLookInput(bPause);
	return APlayerController::SetPause(bPause, CanUnpauseDelegate);
}

bool ATGCOPlayerController::ServerUpdateSpeedOnProps_Validate(class AProps* Props)
{
	return true;
}

void ATGCOPlayerController::ServerUpdateSpeedOnProps_Implementation(class AProps* Props)
{
	if (Props)
	{
		Props->UpdateSpeed();
	}
}

bool ATGCOPlayerController::ServerUpdateSpeedValueOnProps_Validate(class AProps* Props, float fValue)
{
	return true;
}

void ATGCOPlayerController::ServerUpdateSpeedValueOnProps_Implementation(class AProps* Props, float fValue)
{
	if (Props)
	{
		Props->UpdateSpeedValue(fValue);
	}
}

bool ATGCOPlayerController::ServerUpdateVisibilityOnMesh_Validate(class UStaticMeshComponent* Mesh)
{
	return true;
}

void ATGCOPlayerController::ServerUpdateVisibilityOnMesh_Implementation(class UStaticMeshComponent* Mesh)
{
	if (Mesh)
	{
		Mesh->SetVisibility(!(Mesh->IsVisible()));
	}
}

void ATGCOPlayerController::ClientAffectSpeedOnFuturFan_Implementation(class AFan* Fan, float _fSpeed)
{
	Fan->RotatingMovement->RotationRate = FRotator(0.f, 0.f, _fSpeed);
	if (Fan->RadialForce)
	{
		Fan->RadialForce->ForceStrength = _fSpeed * 1000;
		Fan->RadialForce->ImpulseStrength = _fSpeed * 0;
	}
}
