#pragma once

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_MonstroStartFind.generated.h"

/** @brief	A AI behavior Task, it's the main task, the montroplante find its goal, player or targetpoint, and goes toward it. */

UCLASS()
class TGCO_API UBTT_MonstroStartFind : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()
public:

	/**********************************************************************************************//**
	 * @brief	Executes the task operation.
	 *
	 * @param 	OwnerComp 	If non-null, the component that owns this item.
	 * @param 	NodeMemory	If non-null, the node memory.
	 *
	 * @return	An EBTNodeResult::Type, Succeed or Fail.
	 **************************************************************************************************/

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory) override;

protected:
	/** @brief	The last time the monstroplante has hit the player. */
	float fLastHitTime;
};