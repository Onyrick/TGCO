// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveElement.h"
#include "SolutionType.h"
#include "TGCOCharacter.h"
#include "SolutionGenerator.generated.h"

/**
 * The Solution Generator, the player has to activated it to acquire the solution
 */
UCLASS()
class TGCO_API ASolutionGenerator : public AInteractiveElement
{
	GENERATED_UCLASS_BODY()

public:
	/** Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	virtual bool OnInteract() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solution")
	TEnumAsByte<ESolutionType::Type> SolutionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class UPointLightComponent* PointLight;

	UFUNCTION(BlueprintCallable, Category = "Color Solution")
	void UpdateColor();

	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	ATGCOCharacter * Player;

};
