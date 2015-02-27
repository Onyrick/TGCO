#pragma once

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_MonstroStartFind.generated.h"

UCLASS()
class TGCO_API UBTT_MonstroStartFind : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory) override;

	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector TargetPointKey;

protected:
	float fLastHitTime;
};