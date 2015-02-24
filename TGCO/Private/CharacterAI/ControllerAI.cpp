#include "TGCO.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharacterAI.h"
#include "ControllerAI.h"

AControllerAI::AControllerAI(const FObjectInitializer& ObjectInitializer) 
: Super(ObjectInitializer)
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BrainComponent = BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	bWantsPlayerState = true;
}

void AControllerAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	ACharacterAI* Bot = Cast<ACharacterAI>(InPawn);

	// start behavior
	if (Bot && Bot->BotBehavior)
	{
		BlackboardComp->InitializeBlackboard(Bot->BotBehavior->BlackboardAsset);

		//PlayerKeyID = BlackboardComp->GetKeyID("PlayerKeyID");

		BehaviorComp->StartTree(*(Bot->BotBehavior));
	}
}

void AControllerAI::BeginInactiveState()
{
	Super::BeginInactiveState();

	AGameState* GameState = GetWorld()->GameState;

	const float MinRespawnDelay = (GameState && GameState->GameModeClass) ? GetDefault<AGameMode>(GameState->GameModeClass)->MinRespawnDelay : 1.0f;

	GetWorldTimerManager().SetTimer(this, &AControllerAI::Respawn, MinRespawnDelay);
}

void AControllerAI::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	// Stop the behaviour tree/logic
	BehaviorComp->StopTree();

	// Stop any movement we already have
	StopMovement();

	// Cancel the repsawn timer
	GetWorldTimerManager().ClearTimer(this, &AControllerAI::Respawn);
}

void AControllerAI::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	// Look toward focus
	FVector FocalPoint = GetFocalPoint();
	if (!FocalPoint.IsZero() && GetPawn())
	{
		FVector Direction = FocalPoint - GetPawn()->GetActorLocation();
		FRotator NewControlRotation = Direction.Rotation();

		NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);

		SetControlRotation(NewControlRotation);

		APawn* const P = GetPawn();
		if (P && bUpdatePawn)
		{
			P->FaceRotation(NewControlRotation, DeltaTime);
		}

	}
}

void AControllerAI::Respawn()
{
	
}