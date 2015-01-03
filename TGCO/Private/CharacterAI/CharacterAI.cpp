#include "TGCO.h"
#include "CharacterAI.h"

UCharacterAI::UCharacterAI(const class FObjectInitializer& PCIP) : Super(PCIP)
{

}

AAIController* ICharacterAI::GetAIController()
{
	unimplemented();
	return NULL;
}

void ICharacterAI::Destroy()
{
	unimplemented();
}

float ICharacterAI::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	unimplemented();
	return -1.f;
}

void ICharacterAI::ReceiveActorBeginOverlapAI(AActor* OtherActor)
{
	unimplemented();
}