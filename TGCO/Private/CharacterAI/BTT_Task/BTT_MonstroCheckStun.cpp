// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "ControllerAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTT_MonstroCheckStun.h"

UBTT_MonstroCheckStun::UBTT_MonstroCheckStun(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	wasStuned = false;
	wasAlive = true;
}

EBTNodeResult::Type UBTT_MonstroCheckStun::ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
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
		if (MonstroCharacter->IsStun())
		{
			wasStuned = true;
		}
		
		if (!MonstroCharacter->IsDead())
		{
			wasAlive = true;
		}

		if ((MonstroCharacter->IsStun() == false && wasStuned) || (MonstroCharacter->IsDead() && wasAlive))
		{
			ATargetPoint *oldTargetPoint = Cast<ATargetPoint>(MyBlackboard->GetValueAsObject("PlayerToChase"));

			MyBlackboard->SetValueAsBool("Avoiding", false);
			if (oldTargetPoint != nullptr)
			{
				oldTargetPoint->Destroy();
			}

			MyBlackboard->SetValueAsObject("PlayerToChase", nullptr);
			for (TActorIterator<ATGCOCharacter> It(GetWorld()); It; ++It)
			{
				if (It->GetController()->IsLocalPlayerController())
				{
					MyBlackboard->SetValueAsObject("PlayerToChase", *It);
					break;
				}
			}
			MonstroCharacter->SpeedDefault();
			wasStuned = false;
			wasAlive = false;
			UE_LOG(LogDebug, Warning, TEXT("Finish Avoiding By Stun Or Die!"));
		}	

		return EBTNodeResult::Succeeded;
	}
}