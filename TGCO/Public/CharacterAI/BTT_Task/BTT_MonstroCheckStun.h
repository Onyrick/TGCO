#pragma once

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_MonstroCheckStun.generated.h"

/** @brief	A AI behavior Task, check if the monstroplante is stunned in order to launch the appropriate task after. */

UCLASS()
class TGCO_API UBTT_MonstroCheckStun : public UBTTask_BlackboardBase
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
	/** @brief	true if was stuned. */
	bool wasStuned;
	/** @brief	true to was alive. */
	bool wasAlive;
};