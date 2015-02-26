#pragma once

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_MonstroFinishAvoiding.generated.h"

UCLASS()
class TGCO_API UBTT_MonstroFinishAvoiding : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory) override;

};