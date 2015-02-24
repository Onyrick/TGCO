// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "ControllerAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TGCOCharacter.h"
#include "BTT_MonstroFinishAvoiding.h"

UBTT_MonstroFinishAvoiding::UBTT_MonstroFinishAvoiding(const class FObjectInitializer& PCIP) : Super(PCIP)
{
}

EBTNodeResult::Type UBTT_MonstroFinishAvoiding::ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
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
		if (MyBlackboard->GetValueAsBool("Avoiding"))
		{
			MyBlackboard->SetValueAsBool("Avoiding", false);
			ATargetPoint *oldTargetPoint = Cast<ATargetPoint>(MyBlackboard->GetValueAsObject("PlayerToChase"));

			if (oldTargetPoint != NULL)
			{
				oldTargetPoint->Destroy();
			}

			for (TActorIterator<ATGCOCharacter> It(GetWorld()); It; ++It)
			{
				if (It->GetController()->IsLocalPlayerController())
				{
					MyBlackboard->SetValueAsObject("PlayerToChase", *It);
					break;
				}
			}
			MonstroCharacter->SpeedDefault();
		}
		
		return EBTNodeResult::Succeeded;
	}
}