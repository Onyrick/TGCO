// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "ControllerAI.h"
#include "MonstroPlante.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnergyCell.h"
#include "BTT_MonstroCheckAndAvoid.h"

UBTT_MonstroCheckAndAvoid::UBTT_MonstroCheckAndAvoid(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	bIsAvoiding = false;
}

EBTNodeResult::Type UBTT_MonstroCheckAndAvoid::ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
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

		if ( MonstroCharacter == NULL )
			return EBTNodeResult::Failed;

		ATGCOCharacter* Player = Cast<ATGCOCharacter>(MyBlackboard->GetValueAsObject("PlayerToChase"));

		// In pursuit of player
		if (MonstroCharacter->m_bNeedToAvoid && Player != NULL && MyBlackboard->GetValueAsBool("Avoiding") == false && MonstroCharacter->IsStun() == false)
		{
			MonstroCharacter->m_bNeedToAvoid = false;

			FVector TargetPointVector = (Player->GetActorLocation() - MonstroCharacter->GetActorLocation()) / 5;

			ATargetPoint* TargetPoint = GetWorld()->SpawnActor<ATargetPoint>(ATargetPoint::StaticClass(), MonstroCharacter->GetActorLocation() + TargetPointVector, FRotator::ZeroRotator);

			TargetPoint->AddActorLocalOffset(FVector(-(Player->GetActorLocation() - MonstroCharacter->GetActorLocation()) / 5));
			int dir = rand() % 2;
			if (dir == 0)
			{
				TargetPoint->AddActorLocalRotation(FRotator(0.f, 60.f, 0.f));
			}
			else
			{
				TargetPoint->AddActorLocalRotation(FRotator(0.f, -60.f, 0.f));
			}
			
			TargetPoint->AddActorLocalOffset(FVector((Player->GetActorLocation() - MonstroCharacter->GetActorLocation()) / 5));

			if (MonstroCharacter->GetAIController() != NULL)
			{
				MonstroCharacter->GetAIController()->StopMovement();
				MyBlackboard->SetValueAsObject("PlayerToChase", TargetPoint);
			}

			MyBlackboard->SetValueAsBool("Avoiding", true);
			MonstroCharacter->SpeedUp();
		}

		//Running away after hitting the player
		ABotTargetPoint* BotTargetPoint = Cast<ABotTargetPoint>(MyBlackboard->GetValueAsObject("PlayerToChase"));

		if (MonstroCharacter->m_bNeedToAvoid && BotTargetPoint != NULL && MyBlackboard->GetValueAsBool("Avoiding") == false && MonstroCharacter->IsStun() == false)
		{
			MonstroCharacter->m_bNeedToAvoid = false;

			FVector TargetPointVector = (BotTargetPoint->GetActorLocation() - MonstroCharacter->GetActorLocation()) / 5;

			ATargetPoint* TargetPoint = GetWorld()->SpawnActor<ATargetPoint>(ATargetPoint::StaticClass(), MonstroCharacter->GetActorLocation() + TargetPointVector, FRotator::ZeroRotator);

			TargetPoint->AddActorLocalOffset(FVector(-(BotTargetPoint->GetActorLocation() - MonstroCharacter->GetActorLocation()) / 5));
			int dir = rand() % 2;
			if (dir == 0)
			{
				TargetPoint->AddActorLocalRotation(FRotator(0.f, 60.f, 0.f));
			}
			else
			{
				TargetPoint->AddActorLocalRotation(FRotator(0.f, -60.f, 0.f));
			}

			TargetPoint->AddActorLocalOffset(FVector((BotTargetPoint->GetActorLocation() - MonstroCharacter->GetActorLocation()) / 5));

			if (MonstroCharacter->GetAIController() != NULL)
			{
				MonstroCharacter->GetAIController()->StopMovement();
				MyBlackboard->SetValueAsObject("PlayerToChase", TargetPoint);
			}

			MonstroCharacter->SpeedUp();
		}

		if ((BotTargetPoint != NULL && MyController->GetPawn()->GetDistanceTo(BotTargetPoint) < 250.f))
		{
			MonstroCharacter->GetAIController()->StopMovement();
			MyBlackboard->SetValueAsObject("PlayerToChase", NULL);
		}
		

		return EBTNodeResult::Succeeded;
	}
}