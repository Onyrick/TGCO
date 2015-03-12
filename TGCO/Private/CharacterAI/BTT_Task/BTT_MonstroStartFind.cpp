// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "ControllerAI.h"
#include "MonstroPlante.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TGCOCharacter.h"
#include "TGCOGameState.h"
#include <limits>
#include "BTT_MonstroStartFind.h"

UBTT_MonstroStartFind::UBTT_MonstroStartFind(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	fLastHitTime = 0.f;
}

EBTNodeResult::Type UBTT_MonstroStartFind::ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBehaviorTreeComponent* MyComp = OwnerComp;
	AControllerAI* MyController = MyComp ? Cast<AControllerAI>(MyComp->GetOwner()) : nullptr;
	if (MyController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		UBlackboardComponent* MyBlackboard = OwnerComp->GetBlackboardComponent();
		AMonstroPlante * MonstroCharacter = Cast<AMonstroPlante>(MyController->GetPawn());

		if ( MonstroCharacter == nullptr )
			return EBTNodeResult::Failed;
		
		if (MonstroCharacter->IsDead() || MonstroCharacter->IsStun() || MonstroCharacter->isReadyToMove() == false)
			return EBTNodeResult::Failed;

		ATGCOCharacter *Player = Cast<ATGCOCharacter>(MyBlackboard->GetValueAsObject("PlayerToChase"));
		MyBlackboard->SetValueAsBool("Avoiding", false);
		MonstroCharacter->GetAIController()->StopMovement();
		MonstroCharacter->SpeedDefault();		

		if (Player == nullptr)
		{
			float distanceMin = std::numeric_limits<float>::max();
			for (TActorIterator<ATGCOCharacter> It(GetWorld()); It; ++It)
			{
				float distance = MyController->GetPawn()->GetDistanceTo(*It);
				if (distance < distanceMin)
				{
					distanceMin = distance;
					Player = *It;
				}
			}
			MyBlackboard->SetValueAsObject("PlayerToChase", Player);
			MyBlackboard->SetValueAsBool("RunningAway", false);
		}
		else if (MyController->GetPawn()->GetDistanceTo(Player) < 250.f)
		{
			float gameTime = this->GetWorld()->GetTimeSeconds();

			if (gameTime - fLastHitTime >= MonstroCharacter->fSpeedHit)
			{
				UE_LOG(LogDebug, Warning, TEXT("Take that, bitch"));
				ATGCOGameState* gameState = Cast<ATGCOGameState>(GetWorld()->GameState);
				gameState->DecreaseEnergy(MonstroCharacter->fPower, true);
				fLastHitTime = gameTime;

				TArray<ABotTargetPoint*> ArrayTargetBot;
				for (TActorIterator<ABotTargetPoint> It(GetWorld()); It; ++It)
				{
					ArrayTargetBot.Push(*It);
				}

				int idtargetpoint = rand() % ArrayTargetBot.Num();
				if (ArrayTargetBot[idtargetpoint] != nullptr)
				{
					MyBlackboard->SetValueAsObject("PlayerToChase", ArrayTargetBot[idtargetpoint]);
					MyBlackboard->SetValueAsBool("RunningAway", true);
				}
				MonstroCharacter->SpeedUp();
			}
		}
	
		return EBTNodeResult::Succeeded;
	}
}