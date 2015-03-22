

#include "TGCO.h"
#include "Net/UnrealNetwork.h"
#include "TGCOGameState.h"
#include "TGCOPlayerController.h"
#include "TGCOCharacter.h"
#include "Minesweeper.h"
#include "MinesweeperBox.h"


AMinesweeperBox::AMinesweeperBox(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, bIsUndermined(false)
, iNeighboursUndermined(0)
, bIsDisplayed(false)
{
	MineFlag = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MineFlag_MinesweeperBox"));
	MineFlag->AttachParent = RootComponent;

	Number = ObjectInitializer.CreateDefaultSubobject<UTextRenderComponent>(this, TEXT("Number_MinesweeperBox"), true );
	Number->SetRelativeRotation(FRotator(90.0, 90.0, 0.0));
	Number->SetRelativeLocation(FVector(0.0,0.0,25.0));
	Number->SetText(TEXT("0"));
	Number->SetWorldSize(150.0);
	Number->SetVisibility(false);
	Number->AttachParent = RootComponent;

	bReplicates = true;
}

void AMinesweeperBox::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsUndermined)
	{
		Explode(OtherActor);
	}
	else
	{
		if (Number != nullptr)
		{
			Number->SetVisibility(true);
		}	
	}
}

void AMinesweeperBox::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Number != nullptr)
	{
		Number->SetVisibility(false);
	}
}

void AMinesweeperBox::SetIsUndermined()
{
	bIsUndermined = !(bIsUndermined);
}

bool AMinesweeperBox::GetIsUndermined()
{
	return bIsUndermined;
}

void AMinesweeperBox::Explode(class AActor* OtherActor)
{
	UE_LOG(LogDebug, Warning, TEXT("BOOM !!!"));
	ATGCOGameState* gameState = Cast<ATGCOGameState>(GetWorld()->GetGameState());
	if (gameState)
	{
		gameState->DecreaseEnergy(50);
	}
	
	ATGCOCharacter* Character = Cast<ATGCOCharacter>(OtherActor);
	if (Character)
	{
		Character->SetActorTransform(Character->GetCheckpoint());
	}
	
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains("Minesweeper") && ActorItr->GetActorClass()->GetDescription() == FString(TEXT("Minesweeper BP")) )
		{
			UE_LOG(LogTest, Warning, TEXT("Call Reset Minesweeper on Minesweeper"));
			AMinesweeper* Minesweeper = Cast<AMinesweeper>(*ActorItr);
			Minesweeper->ResetMinesweeper();
		}
	}
}

void AMinesweeperBox::SetNeighboursUndermined()
{
	UE_LOG(LogDebug, Warning, TEXT("Set neighbours undermined"));
	iNeighboursUndermined += 1;
	// Object has authority
	if (!(Role < ROLE_Authority))
	{
		UE_LOG(LogDebug, Warning, TEXT("No authority: change the Text render Number"));
		if (Number != nullptr)
		{
			Number->SetText(FString::Printf(TEXT("%d"), iNeighboursUndermined));
		}
	}
}

unsigned int AMinesweeperBox::GetNeighboursUndermined()
{
	return iNeighboursUndermined;
}

void AMinesweeperBox::SetIsMarked()
{
	bIsMarked = !bIsMarked;
	if (!(Role < ROLE_Authority))
	{
		SetVisibilityOfFlag();
	}
}

bool AMinesweeperBox::IsMarked()
{
	return bIsMarked;
}

void AMinesweeperBox::SetVisibilityOfFlag()
{
	if (Role < ROLE_Authority)
	{
		UE_LOG(LogDebug, Warning, TEXT("No authority : call ServerUpdateVisibilityOnMesh"));
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerUpdateVisibilityOnMesh(this);
		}
	}
	else
	{
		UE_LOG(LogDebug, Warning, TEXT("Authority : Set the visibility of flag"));
		bIsMarked = !bIsMarked;
		MineFlag->SetVisibility(!(MineFlag->IsVisible()));
	}
}

void AMinesweeperBox::OnRep_TextRender()
{
	if (Number != nullptr)
	{
		Number->SetText(FString::Printf(TEXT("%d"), iNeighboursUndermined));
	}
	
}

void AMinesweeperBox::OnRep_Flag()
{
	UE_LOG(LogDebug, Warning, TEXT("i'm on OnRep_Flag"));
	if (MineFlag != nullptr)
	{
		MineFlag->SetVisibility(!(MineFlag->IsVisible()));
	}
}

void AMinesweeperBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AMinesweeperBox, iNeighboursUndermined);
	DOREPLIFETIME(AMinesweeperBox, Number);
	DOREPLIFETIME(AMinesweeperBox, bIsUndermined);
	DOREPLIFETIME(AMinesweeperBox, MineFlag);
	DOREPLIFETIME(AMinesweeperBox, bIsMarked);
}
