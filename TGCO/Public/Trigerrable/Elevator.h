// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Trigerrable.h"
#include "TGCOCharacter.h"
#include "Elevator.generated.h"


/**
*
*/
UCLASS()
class TGCO_API AElevator : public ATrigerrable
{
	GENERATED_UCLASS_BODY()

public:
	/**
	*Event launch when Player trigger the component.
	* Set the Player inside the AElevator
	*/
		virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
	/**
	*Event launch when Player trigger the component.
	* Set the Player outside the AElevator
	*/
		virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	/**
	* Get the staticMesh of the front doors
	*/
		UStaticMeshComponent* GetFrontDoors();

	/**
	* Get the statiicMesh of the back doors
	*/
		UStaticMeshComponent* GetBackDoors();

		/**
		*Check if both Player are in their own AElevator to change Level
		*/
		bool CheckPlayersPresence();

		/**
		*Close the AElevator's doors when both Players are inside
		*/
		void CloseFrontDoors();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	UStaticMeshComponent* FrontDoors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	UStaticMeshComponent* BackDoors;
};
