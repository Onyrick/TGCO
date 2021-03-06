
#pragma once

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BotTargetPoint.h"
#include "BTT_FixBotStartFind.generated.h"

UCLASS()
class TGCO_API UBTT_FixBotStartFind : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_FixBotStartFind(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory) override;

	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector TargetPointKey;

private:
	bool BeginToRun;
	ABotTargetPoint* BotTargetPoint;
};
