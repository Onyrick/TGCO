

#include "TGCO.h"
#include "Net/UnrealNetwork.h"
#include "TGCOGameState.h"
#include "TGCOPlayerController.h"
#include "TGCOCharacter.h"
#include "Minesweeper.h"
#include "MinesBox.h"


AMinesBox::AMinesBox(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, bIsUndermined(false)
, iNeighboursUndermined(0)
, bIsDisplayed(false)
{
	MineFlag = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MineFlag_MineBox"));
	MineFlag->AttachParent = RootComponent;

	Number = ObjectInitializer.CreateDefaultSubobject<UTextRenderComponent>(this, TEXT("Number_MineBox"), true );
	Number->SetRelativeRotation(FRotator(90.0, 90.0, 0.0));
	Number->SetRelativeLocation(FVector(0.0,0.0,25.0));
	Number->SetText(TEXT("0"));
	Number->SetWorldSize(150.0);
	Number->SetVisibility(false);
	Number->AttachParent = RootComponent;

	bReplicates = true;
}

void AMinesBox::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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

void AMinesBox::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Number != nullptr)
	{
		Number->SetVisibility(false);
	}
}

void AMinesBox::SetIsUndermined()
{
	//UE_LOG(LogTest, Warning, TEXT("Je suis dans la fonction SetIsUndermined de MineBox"));
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
		if (ActorItr->GetName().Contains("Minesweeper_Futur") && ActorItr->GetActorClass()->GetDescription() == FString(TEXT("Minesweeper BP")) )
		{
			AMinesweeper* Minesweeper = Cast<AMinesweeper>(*ActorItr);
			Minesweeper->ResetMinesweeper();
		}
	}
}

void AMinesBox::SetNeighboursUndermined()
{
	//UE_LOG(LogDebug, Warning, TEXT("Set neighbours undermined"));
	iNeighboursUndermined += 1;
	// Object has authority
	if (!(Role < ROLE_Authority))
	{
		Number->SetText(FString::Printf(TEXT("%d"), iNeighboursUndermined));
	}
}

unsigned int AMinesBox::GetNeighboursUndermined()
{
	return iNeighboursUndermined;
}

void AMinesBox::SetIsMarked()
{
	bIsMarked = !bIsMarked;
	if (!(Role < ROLE_Authority))
	{
		SetVisibilityOfFlag();
	}
}

void AMinesBox::SetVisibilityOfFlag()
{
	/*if (Role < ROLE_Authority)
	{
		UE_LOG(LogDebug, Warning, TEXT("No authority : call ServerSetFlagVisibility"));
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerUpdateVisibilityOnMesh(MineFlag);
		}
	}
	else
	{*/
		UE_LOG(LogDebug, Warning, TEXT("Authority : Set the visibility of flag"));
		MineFlag->SetVisibility(!(MineFlag->IsVisible()));
	//}
}



void AMinesBox::OnRep_TextRender()
{
	if (Number != NULL)
	{
		Number->SetText(FString::Printf(TEXT("%d"), iNeighboursUndermined));
	}
	
}

void AMinesBox::OnRep_Flag()
{
	UE_LOG(LogDebug, Warning, TEXT("i'm on OnRep_Flag"));
	if (MineFlag != NULL)
	{
		MineFlag->SetVisibility(!(MineFlag->IsVisible()));
	}
}

void AMinesBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AMinesBox, iNeighboursUndermined);
	DOREPLIFETIME(AMinesBox, Number);
	DOREPLIFETIME(AMinesBox, bIsUndermined);
	DOREPLIFETIME(AMinesBox, MineFlag);
}
