

#include "TGCO.h"
#include "TGCOGameState.h"
#include "TGCOCharacter.h"
#include "Minesweeper.h"
#include "MinesBox.h"


AMinesBox::AMinesBox(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, bIsUndermined(false)
, iNeighboursUndermined(0)
, bIsDisplayed(false)
{
	Number = ObjectInitializer.CreateDefaultSubobject<UTextRenderComponent>(this, TEXT("Number_MineBox"), true );
	Number->SetRelativeRotation(FRotator(90.0, 90.0, 0.0));
	Number->SetRelativeLocation(FVector(0.0,0.0,25.0));
	Number->SetText(TEXT("0"));
	Number->SetWorldSize(150.0);
	Number->SetVisibility(false);
	Number->AttachParent = RootComponent;
}

void AMinesBox::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsUndermined)
	{
		Explode(OtherActor);
	}
	else
	{
		if (Number != NULL)
		{
			Number->SetVisibility(true);
		}	
	}
}

void AMinesBox::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Number != NULL)
	{
		Number->SetVisibility(false);
	}
}

void AMinesBox::SetIsUndermined()
{
	bIsUndermined = !(bIsUndermined);
}

bool AMinesBox::GetIsUndermined()
{
	return bIsUndermined;
}

void AMinesBox::Explode(class AActor* OtherActor)
{
	UE_LOG(LogDebug, Warning, TEXT("BOOM !!!"));
	ATGCOGameState* gameState = Cast<ATGCOGameState>(GetWorld()->GetGameState());
	if (gameState)
	{
		gameState->DecreaseEnergy(5);
	}
	ATGCOCharacter* Character = Cast<ATGCOCharacter>(OtherActor);
	if (Character)
	{
		Character->SetActorTransform(Character->GetCheckpoint());
	}
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains("Minesweeper"))
		{
			AMinesweeper* Minesweeper = Cast<AMinesweeper>(*ActorItr);
			Minesweeper->ResetMinesweeper();
		}
	}
}

void AMinesBox::SetNeighboursUndermined()
{
	iNeighboursUndermined += 1;
}

unsigned int AMinesBox::GetNeighboursUndermined()
{
	return iNeighboursUndermined;
}