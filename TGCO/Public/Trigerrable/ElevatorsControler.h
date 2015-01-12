

#pragma once


#include "GameFramework/Actor.h"
#include "Elevator.h"
#include "TGCOCharacter.h"
#include "ElevatorsControler.generated.h"



/**
*
*/
UCLASS()
class TGCO_API AElevatorsControler : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	void PlayAnim();
	/**
	*Check if both Player are in their own AElevator to change Level
	*/
	bool CheckPlayersPresence();

	/**
	*Close the AElevator's doors when both Players are inside
	*/
	void CloseFrontDoors();

	/**
	*Play a sound when AElevator's doors are closing/closed/opening
	*/
	void PlaySound();

	/**
	*Open the AElevator's doors when sound is finished and the next Level is load
	*/
	void OpenBackDoors();

private:
	AElevator* FuturElevator;

	AElevator* PastElevator;
};