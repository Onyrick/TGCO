#pragma once

#include "AIController.h"
#include "CharacterAI.generated.h"

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UCharacterAI :
	public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICharacterAI{
	GENERATED_IINTERFACE_BODY()
public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Function to get the AIController
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "CharacterAI", meta = (FriendlyName = "GetAIController"))
		virtual AAIController* GetAIController();
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Event launch when the Character has to be destroyed
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "CharacterAI", meta = (FriendlyName = "Destroy"))
		virtual void Destroy();

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Event launch when the Character take damage
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "CharacterAI", meta = (FriendlyName = "TakeDamage"))
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) = 0;
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Event launch when the Character is hit by another actor
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "CharacterAI", meta = (FriendlyName = "ReceiveActorBeginOverlap"))
		virtual void ReceiveActorBeginOverlapAI(AActor* OtherActor);
	
};