

#include "TGCO.h"
#include "TGCOPlayerController.h"
#include "ConsoleMinesweeper.h"


AConsoleMinesweeper::AConsoleMinesweeper(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, bInGame(true)
{
	bReplicates = true;
}

bool AConsoleMinesweeper::OnInteract()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			if (bInGame)
			{
				UE_LOG(LogTest, Warning, TEXT("Console activate"));
				PlayerController->SetViewTargetWithBlend(CameraConsole, 1.5, EViewTargetBlendFunction::VTBlend_EaseInOut, 1.0, true);
				EnableInput(PlayerController);
				PlayerController->SetIgnoreMoveInput(true);
				PlayerController->SetIgnoreLookInput(true);
				PlayerController->bShowMouseCursor = true;
				PlayerController->bEnableClickEvents = true;
				PlayerController->bEnableMouseOverEvents = true;
				bInGame = false;
			}
			else
			{
				UE_LOG(LogTest, Warning, TEXT("Console desactivate"));
				ACharacter* PlayerCharacter = PlayerController->GetCharacter();
				PlayerController->SetViewTargetWithBlend(PlayerCharacter, 1.5, EViewTargetBlendFunction::VTBlend_EaseInOut, 1.0, true);
				DisableInput(PlayerController);
				PlayerController->SetIgnoreMoveInput(false);
				PlayerController->SetIgnoreLookInput(false);
				PlayerController->bShowMouseCursor = false;
				PlayerController->bEnableClickEvents = false;
				PlayerController->bEnableMouseOverEvents = false;
				bInGame = true;
			}
		}
	}

	return true;
}

void AConsoleMinesweeper::ResetMinesweeper_Implementation()
{
	UE_LOG(LogTest, Warning, TEXT("Je suis dans ResetMinesweeper"));
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains("Minesweeper_Futur") && ActorItr->GetActorClass()->GetDescription() == FString(TEXT("Minesweeper BP")))
		{
			AMinesweeper* Minesweeper = Cast<AMinesweeper>(*ActorItr);
			Minesweeper->GetMineBoxAt(0)->SetVisibilityOfFlag();
		}
	}
}

