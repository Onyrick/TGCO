// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster.h"
#include "SolutionType.h"
#include "BotTargetPoint.h"
#include "EnergyCell.h"
#include "MonstroPlante.generated.h"

/**
 *	TODO
 */
UCLASS()
class TGCO_API AMonstroPlante : public AMonster
{
	GENERATED_UCLASS_BODY()

public:
	/** Event launch when the FixBot take damage */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	/** Event launched when the monster has to be destroyed */
	virtual void Destroyed();

	void AddNewResistenceSolution(ESolutionType::Type _solution);
	void RemoveResistenceSolution(ESolutionType::Type _solution);
	void RespawnAI();

	UPROPERTY(EditAnywhere, Category = "SpawnPoint")
	ABotTargetPoint* SpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Characteristics")
	float fSpeedHit;

	UPROPERTY(EditAnywhere, Category = "Characteristics")
	float fPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class UStaticMeshComponent* SolutionSphere1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class UStaticMeshComponent* SolutionSphere2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class UStaticMeshComponent* SolutionSphere3;

	UPROPERTY(EditAnywhere, Category = "Triggers")
	UBoxComponent* TriggerBox;

	/** When a projectile enter the box, the monster will try to avoid it */
	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void UnStun() override;

	void UpdateLights();
	void SpeedUp();
	void SpeedDefault();

	bool m_bNeedToAvoid;

protected:	
	TArray<ESolutionType::Type> SolutionResistence;
	UMaterialInstanceDynamic *MaterialInstance1;
	UMaterialInstanceDynamic *MaterialInstance2;
	UMaterialInstanceDynamic *MaterialInstance3;

	virtual void Tick(float DeltaSeconds) override;

	int m_iIdToReplace;

};
