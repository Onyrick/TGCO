

#include "TGCO.h"
#include "TGCOPlayerState.h"
#include "Net/UnrealNetwork.h"

ATGCOPlayerState::ATGCOPlayerState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, PlayerNumber(0)
, PropsAffectedByTime(nullptr)
, ModUsedOnProp(EShootMode::NONE)
, eCurrentState(EPlayerStatus::IN_GAME)
{
	bReplicates = true;
}

int32 ATGCOPlayerState::GetPlayerNumber()
{
	return PlayerNumber;
}

void ATGCOPlayerState::SetPlayerNumber(int32 NewPlayerNumber)
{
	UE_LOG(LogTest, Warning, TEXT("Update from server (PlayeState is %i) : from %i to %i "), this->GetUniqueID(), PlayerNumber, NewPlayerNumber);
	PlayerNumber = NewPlayerNumber;
}

void ATGCOPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATGCOPlayerState, PlayerNumber);
}

bool ATGCOPlayerState::ServerSetPlayerNumber_Validate(int32 NewPlayerNumber)
{
	UE_LOG(LogTest, Warning, TEXT("Validate server exchange"));
	return true;
}

void ATGCOPlayerState::ServerSetPlayerNumber_Implementation(int32 NewPlayerNumber)
{
	UE_LOG(LogTest, Warning, TEXT("Update from client (PlayeState is %i) : from %i to %i "), this->GetUniqueID(), PlayerNumber, NewPlayerNumber);
	PlayerNumber = NewPlayerNumber;
}

void ATGCOPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	ATGCOPlayerState* TGCOPlayer = Cast<ATGCOPlayerState>(PlayerState);
	if (TGCOPlayer)
	{
		TGCOPlayer->PlayerNumber = PlayerNumber;
	}
}

void ATGCOPlayerState::AddNewInventoryItem(AStockable* _item)
{
	InventoryListItems.Add(_item);
	UE_LOG(LogTest, Warning, TEXT("Number of element %d "), InventoryListItems.Num());

}

void ATGCOPlayerState::RemoveInventoryItem(AStockable* _item)
{
	InventoryListItems.Remove(_item);
}

TArray<AStockable*> ATGCOPlayerState::GetInventoryListItems()
{
	return InventoryListItems;
}

void ATGCOPlayerState::SetPropsAffected(AProps* PropsAffected)
{
	if (PropsAffectedByTime)
	{
		PropsAffectedByTime->ReinitSpeed();
	}
	PropsAffectedByTime = PropsAffected;
}

bool ATGCOPlayerState::IsPropsAffected()
{
	return PropsAffectedByTime != nullptr;
}

EShootMode::Type ATGCOPlayerState::GetModUsed()
{
	return ModUsedOnProp;
}

void ATGCOPlayerState::SetModUsed(EShootMode::Type _mod)
{
	ModUsedOnProp = _mod;
}

void ATGCOPlayerState::SwitchGamePuzzle(AActor* NewViewTarget)
{
	if (eCurrentState == EPlayerStatus::IN_GAME)
	{
		// Go to puzzle game state
		UWorld* World = GetWorld();
		if (World)
		{
			APlayerController* PlayerController = World->GetFirstPlayerController();
			if (PlayerController)
			{
				// Move to the camera puzzle
				PlayerController->SetViewTargetWithBlend(NewViewTarget, 1.5, EViewTargetBlendFunction::VTBlend_EaseInOut, 1.0, true);
				// Inputs
				EnableInput(PlayerController);
				PlayerController->SetIgnoreMoveInput(true);
				PlayerController->SetIgnoreLookInput(true);
				PlayerController->bEnableClickEvents = true;
				PlayerController->bEnableMouseOverEvents = true;
				PlayerController->bShowMouseCursor = true;

				// Change Input mode
				FInputModeGameAndUI Mode;
				PlayerController->SetInputMode(Mode);

				eCurrentState = EPlayerStatus::IN_PUZZLE_GAME;
			}
		}
	}
	else
	{
		if (eCurrentState == EPlayerStatus::IN_PUZZLE_GAME)
		{
			// Go to game state
			UWorld* World = GetWorld();
			if (World)
			{
				APlayerController* PlayerController = World->GetFirstPlayerController();
				if (PlayerController)
				{
					// Move to the camera of the player
					PlayerController->SetViewTargetWithBlend(NewViewTarget, 1.5, EViewTargetBlendFunction::VTBlend_EaseInOut, 1.0, true);
					// Inputs
					DisableInput(PlayerController);
					PlayerController->SetIgnoreMoveInput(false);
					PlayerController->SetIgnoreLookInput(false);
					PlayerController->bShowMouseCursor = false;
					PlayerController->bEnableClickEvents = false;
					PlayerController->bEnableMouseOverEvents = false;
					
					// Change game mode
					FInputModeGameOnly GameMode;
					PlayerController->SetInputMode(GameMode);

					eCurrentState = EPlayerStatus::IN_GAME;
				}
			}
		}
	}
}
