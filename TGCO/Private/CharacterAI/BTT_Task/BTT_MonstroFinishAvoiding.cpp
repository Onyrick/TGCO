
#include "TGCO.h"
#include "ControllerAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TGCOCharacter.h"
#include "BTT_MonstroFinishAvoiding.h"

UBTT_MonstroFinishAvoiding::UBTT_MonstroFinishAvoiding(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

EBTNodeResult::Type UBTT_MonstroFinishAvoiding::ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
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
		if (MyBlackboard->GetValueAsBool("Avoiding"))
		{
			MyBlackboard->SetValueAsBool("Avoiding", false);
			ATargetPoint *oldTargetPoint = Cast<ATargetPoint>(MyBlackboard->GetValueAsObject("PlayerToChase"));

			if (oldTargetPoint != nullptr)
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