#pragma once

#include "AIController.h"
#include "ControllerAI.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class TGCO_API AControllerAI : public AAIController
{
	GENERATED_BODY()

public:
	AControllerAI(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(transient)
	UBlackboardComponent* BlackboardComp;

	/* Cached BT component */
	UPROPERTY(transient)
	UBehaviorTreeComponent* BehaviorComp;

	void Respawn();
	
protected:
	int32 PlayerKeyID;

public:

	// Begin AController interface
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	virtual void Possess(class APawn* InPawn) override;
	virtual void BeginInactiveState() override;
	// End APlayerController interface

	// Begin AAIController interface
	/** Update direction AI is looking based on FocalPoint */
	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;
	// End AAIController interface

	/** Returns BlackboardComp subobject **/
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }
};