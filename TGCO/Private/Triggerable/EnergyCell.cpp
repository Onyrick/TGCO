
#include "TGCO.h"
#include "TGCOGameState.h"
#include "Engine.h"
#include "TGCOCharacter.h"
#include "EnergyCell.h"

AEnergyCell::AEnergyCell(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, iAmountOfEnergy(100)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> EnergyShape(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Statue'"));
	StaticMesh->SetStaticMesh(EnergyShape.Object);
	StaticMesh->SetRelativeScale3D(FVector(0.5,0.5,0.5));
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AEnergyCell::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ATGCOCharacter *Player = Cast<ATGCOCharacter>(OtherActor);
	if (Player != nullptr)
	{
		Consumed();
	}
}

void AEnergyCell::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{}

void AEnergyCell::Consumed()
{
 	ATGCOGameState* gameState = Cast<ATGCOGameState>(GetWorld()->GetGameState());
 	if (gameState)
 	{
 		gameState->IncreaseEnergyMax(iAmountOfEnergy);
 	}

	if (Destroy(true, false))
	{
		UE_LOG(LogDebug, Warning, TEXT("Energy cell consumed"));
	}
}

int32 AEnergyCell::GetAmountOfEnergy()
{
	return iAmountOfEnergy;
}

void AEnergyCell::SetAmountOfEnergy(int32 _amount)
{
	iAmountOfEnergy = _amount;
}
