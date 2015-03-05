

#include "TGCO.h"
#include "TGCOPlayerController.h"
#include "ConsoleMinesweeper.h"


AConsoleMinesweeper::AConsoleMinesweeper(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bReplicates = true;
}


void AConsoleMinesweeper::CreateConsoleMinesweeper()
{
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains("Minesweeper_Futur") && ActorItr->GetActorClass()->GetDescription() == FString(TEXT("Minesweeper BP")))
		{
			AMinesweeper* _Minesweeper = Cast<AMinesweeper>(*ActorItr);
			Minesweeper = _Minesweeper;
		}
	}

	/*if (Role < ROLE_Authority)
	{
		UE_LOG(LogTest, Warning, TEXT("Pas autorité, appel de ServerCreateConsoleMinesweeper"));
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			Console = PC->ServerCreateConsoleMinesweeper();
		}
		
	}
	else
	{
		UE_LOG(LogTest, Warning, TEXT("autorité, Create Console Minesweeper"));
		
		/*for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			UE_LOG(LogTest, Warning, TEXT("Create Console Minesweeper Widget"));
			APlayerController* player = Cast<APlayerController>(*Iterator);
			Console = CreateWidget<UConsoleMinesweeperUMG>(player, Console->GetClass());
			break;
		}		
	}*/
}

bool AConsoleMinesweeper::OnInteract()
{
	UE_LOG(LogTest, Warning, TEXT("Console activate"));
	return true;
}

void AConsoleMinesweeper::ResetMinesweeper_Implementation()
{
	UE_LOG(LogTest, Warning, TEXT("Je suis dans ResetMinesweeper"));
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains("Minesweeper_Futur") && ActorItr->GetActorClass()->GetDescription() == FString(TEXT("Minesweeper BP")))
		{
			AMinesweeper* _Minesweeper = Cast<AMinesweeper>(*ActorItr);
			Minesweeper = _Minesweeper;
		}
	}
}

void AConsoleMinesweeper::OnRep_Minesweeper()
{
	UE_LOG(LogTest, Warning, TEXT("Je suis dans OnRep_Minesweeper"));
	Minesweeper->GetMineBoxAt(0)->SetVisibilityOfFlag();
}

void AConsoleMinesweeper::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AConsoleMinesweeper, Minesweeper);
	//DOREPLIFETIME(AConsoleMinesweeper, Console);
}
