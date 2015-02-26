

#include "TGCO.h"
#include "Runtime/UMG/Public/UMG.h"
#include "SlateBasics.h"
#include "ConsoleMinesweeper.h"


AConsoleMinesweeper::AConsoleMinesweeper(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bReplicates = true;
}

bool AConsoleMinesweeper::ServerCreateConsoleMinesweeper_Validate()
{
	return true;
}

void AConsoleMinesweeper::ServerCreateConsoleMinesweeper_Implementation()
{
	UE_LOG(LogTest, Warning, TEXT("Je suis dans ServerCreateConsoleMinesweeper"));
	CreateConsoleMinesweeper();
}

void AConsoleMinesweeper::CreateConsoleMinesweeper()
{
	if (Role < ROLE_Authority)
	{
		UE_LOG(LogTest, Warning, TEXT("Pas autorité, appel de ServerCreateConsoleMinesweeper"));
		ServerCreateConsoleMinesweeper();
		UE_LOG(LogTest, Warning, TEXT("Post appel de ServerCreateConsoleMinesweeper"));	
	}
	else
	{
		UE_LOG(LogTest, Warning, TEXT("autorité, Create Console Minesweeper"));
		for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			if (ActorItr->GetName().Contains("Minesweeper_Futur") && ActorItr->GetActorClass()->GetDescription() == FString(TEXT("Minesweeper BP")))
			{
				AMinesweeper* _Minesweeper = Cast<AMinesweeper>(*ActorItr);
				Minesweeper = _Minesweeper->GetClass();
			}
		}
		UE_LOG(LogTest, Warning, TEXT("Hello !!!"));

		/*for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			UE_LOG(LogTest, Warning, TEXT("Create Console Minesweeper Widget"));
			APlayerController* player = Cast<APlayerController>(*Iterator);
			Console = CreateWidget<UConsoleMinesweeperUMG>(player, Console->GetClass());
			break;
		}*/
		
		
	}
}

bool AConsoleMinesweeper::OnInteract()
{
	UE_LOG(LogTest, Warning, TEXT("Console activate"));
	return true;
}

void AConsoleMinesweeper::ResetMinesweeper_Implementation()
{
}

void AConsoleMinesweeper::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AConsoleMinesweeper, Minesweeper);
	//DOREPLIFETIME(AConsoleMinesweeper, Console);
}
