

#include "TGCO.h"
#include "TGCOPlayerController.h"
#include "TGCOGameInstance.h"
#include "GameFramework/PlayerInput.h"

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
};

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
