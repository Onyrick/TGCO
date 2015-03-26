

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


void AOpenBarrierConsole::SetOpeningCodeFromServer(int32 code)
{
	SetCode(code);
}

void AOpenBarrierConsole::SetCode(int32 code)
{
	OpeningCode = code;
	if (Displayer != nullptr)
	{
		//auto check = Displayer->CodeToDisplay;
		//std::string MyStdString(TCHAR_TO_UTF8(*check));
		Displayer->SetCodeToDisplay(FString::FromInt(OpeningCode));
		//check = Displayer->CodeToDisplay;
		//std::string My2StdString(TCHAR_TO_UTF8(*check));
		//Displayer->SendCodeReadyEvent();
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