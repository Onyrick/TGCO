#pragma once

#include "GameFramework/Actor.h"
#include "Monster.h"
#include "FixBot.generated.h"

UCLASS()
class TGCO_API AFixBot : public AMonster
{
	GENERATED_UCLASS_BODY()
public:

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Event launch when the Character take damage
	//////////////////////////////////////////////////////////////////////////////////////////////
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);
	
	
};