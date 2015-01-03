// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Trigerrable.h"
#include "EnergyCell.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API AEnergyCell : public AActor, public ITrigerrable
{
	GENERATED_UCLASS_BODY()

public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Event launch when Player trigger the component.
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "EnergyCell", meta = (FriendlyName = "OnComponentBeginOverlap"))
		virtual void OnComponentBeginOverlap();

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Event launch when Player trigger the component.
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "EnergyCell", meta = (FriendlyName = "OnComponentEndOverlap"))
		virtual void OnComponentEndOverlap();

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Set the AEnergyCell as consumed when the Player hit the OnComponentBeginOverlap. 
	//Hide the AEnergyCell in the Level. Increase Player's energy
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "EnergyCell", meta = (FriendlyName = "Consumed"))
		void Consumed();

	//Getter / Setter / Is
	UFUNCTION(BlueprintCallable, Category = "EnergyCell", meta = (FriendlyName = "GetAmountOfEnergy"))
	int32 GetAmountOfEnergy();

	UFUNCTION(BlueprintCallable, Category = "EnergyCell", meta = (FriendlyName = "SetAmountOfEnergy"))
	void SetAmountOfEnergy(int32 _unlock);

protected:
	int32 iAmountOfEnergy; //The amount of energy containing in the cell
};
