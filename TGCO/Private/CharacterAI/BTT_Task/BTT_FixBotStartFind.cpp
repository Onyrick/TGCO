// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "ControllerAI.h"
#include "FixBot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTT_FixBotStartFind.h"

UBTT_FixBotStartFind::UBTT_FixBotStartFind(const FObjectInitializer& ObjectInitializer) 
: Super(ObjectInitializer)
, BeginToRun(true)
{
	BotTargetPoint = nullptr;
}

EBTNodeResult::Type UBTT_FixBotStartFind::ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
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
		AFixBot * FixBotCharacter = Cast<AFixBot>(MyController->GetPawn());

		/*if (BotTargetPoint != NULL && FixBotCharacter->GetDistanceTo(BotTargetPoint) > 60.f)
		{
			return EBTNodeResult::Failed;
		}*/
		
		if (FixBotCharacter->MaxRoutes < 1)
		{
			return EBTNodeResult::Failed;
		}

		BeginToRun = false;

		//Demarrage
		int StartID = rand() % FixBotCharacter->MaxRoutes;

		//Direction
		int TargetID;
		do 
		{
			TargetID = rand() % FixBotCharacter->MaxRoutes;
		} while (TargetID == StartID);

		if (FixBotCharacter == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		for (TActorIterator<ABotTargetPoint> It(GetWorld()); It; ++It)
		{
			ABotTargetPoint* BotTargetPoint = *It;

			if (BotTargetPoint->iIDTargetPoint == StartID)
			{
				//On place le FixBot sur le point de départ
				FixBotCharacter->SetActorLocation(BotTargetPoint->GetActorLocation());
			}
			if (BotTargetPoint->iIDTargetPoint == TargetID)
			{
				//On enregistre le point qu'il devra atteindre
				MyBlackboard->SetValueAsVector("TargetPoint", BotTargetPoint->GetActorLocation());
			}
		}

		return EBTNodeResult::Succeeded;
	}
}
