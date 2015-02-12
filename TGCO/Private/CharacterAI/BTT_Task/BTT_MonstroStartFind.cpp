// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "ControllerAI.h"
#include "MonstroPlante.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TGCOCharacter.h"
#include "TGCOGameState.h"
#include "BTT_MonstroStartFind.h"

UBTT_MonstroStartFind::UBTT_MonstroStartFind(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	fLastHitTime = 0.f;
}

EBTNodeResult::Type UBTT_MonstroStartFind::ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBehaviorTreeComponent* MyComp = OwnerComp;
	AControllerAI* MyController = MyComp ? Cast<AControllerAI>(MyComp->GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		UBlackboardComponent* MyBlackboard = OwnerComp->GetBlackboardComponent();
		AMonstroPlante * MonstroCharacter = Cast<AMonstroPlante>(MyController->GetPawn());

		if ( MonstroCharacter == NULL )
			return EBTNodeResult::Failed;
		
		ATGCOCharacter *Player = Cast<ATGCOCharacter>(MyBlackboard->GetValueAsObject("PlayerToChase"));

		if (Player == NULL)
		{
			for (TActorIterator<ATGCOCharacter> It(GetWorld()); It; ++It)
			{
				if (It->GetController()->IsLocalPlayerController())
				{
					MyBlackboard->SetValueAsObject("PlayerToChase", *It);
					break;
				}
			}
		}
		else
		{
			if (MyController->GetPawn()->GetDistanceTo(Player) < 250.f)
			{
				float gameTime = this->GetWorld()->GetTimeSeconds();

				if (gameTime - fLastHitTime >= MonstroCharacter->fSpeedHit)
				{
					UE_LOG(LogDebug, Warning, TEXT("Take that, bitch"));
					ATGCOGameState* gameState = Cast<ATGCOGameState>(GetWorld()->GameState);
					gameState->DecreaseEnergy(MonstroCharacter->fPower);
					fLastHitTime = gameTime;
				}
			}
		}

		return EBTNodeResult::Succeeded;
	}
}