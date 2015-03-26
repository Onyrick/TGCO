

#include "TGCO.h"
#include <ctime>
#include <cstdlib>
#include "Utils.h"
#include "OpenBarrierConsole.h"
#include <string>
#include "TGCOPlayerController.h"
#include "Net/UnrealNetwork.h"


AOpenBarrierConsole::AOpenBarrierConsole(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	Displayer(nullptr),
	OpeningCode(0)
{
}


bool AOpenBarrierConsole::OnInteract()
{
	/*When the player interact with the console it activates the camera to enter in puzzle mode*/
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			ATGCOPlayerState* PlayerState = Cast<ATGCOPlayerState>(PlayerController->PlayerState);
			if (PlayerState)
			{
				if (PlayerState->eCurrentState == EPlayerStatus::IN_GAME)
				{
					PlayerState->SwitchGamePuzzle(CameraPuzzle);
				}
				else
				{
					if (PlayerState->eCurrentState == EPlayerStatus::IN_PUZZLE_GAME)
					{
						PlayerState->SwitchGamePuzzle(PlayerController->GetCharacter());
					}
				}
			}
		}
	}
	return true;
}

void AOpenBarrierConsole::SetOpeningCode(int32 code)
{
	/*Different behavior if we are server or client.*/
	if (Role < ROLE_Authority)
	{
		SetCode(code);
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerSetOpeningCode(this, code);
		}
	}
}

/*Set the code sent by the server*/
void AOpenBarrierConsole::SetOpeningCodeFromServer(int32 code)
{
	SetCode(code);
}

/*When the code is received the displayer is updated*/
void AOpenBarrierConsole::SetCode(int32 code)
{
	OpeningCode = code;
	if (Displayer != nullptr)
	{
		Displayer->SetCodeToDisplay(FString::FromInt(OpeningCode));
	}
}

bool AOpenBarrierConsole::CheckCode(int32 code)
{
	if (code == OpeningCode)
	{
		for (auto barrier : ControledTerminals)
		{
			barrier->SetActiveState(false);
		}
		return true;
	}
	return false;
}


void AOpenBarrierConsole::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AOpenBarrierConsole, OpeningCode);
	DOREPLIFETIME(AOpenBarrierConsole, Displayer);
}