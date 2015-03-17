

#include "TGCO.h"
#include "TGCOPlayerState.h"
#include "Net/UnrealNetwork.h"

ATGCOPlayerState::ATGCOPlayerState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, PlayerNumber(0)
, PropsAffectedByTime(nullptr)
, ModUsedOnProps(EShootMode::NONE)
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
	check(PlayerState);
	Super::CopyProperties(PlayerState);

	ATGCOPlayerState* TGCOPlayer = Cast<ATGCOPlayerState>(PlayerState);
	if (TGCOPlayer != nullptr)
	{
		TGCOPlayer->PlayerNumber = PlayerNumber;
	}
}

void ATGCOPlayerState::AddNewInventoryItem(AStockable* _item)
{
	check(_item);
	InventoryListItems.Add(_item);
	UE_LOG(LogTest, Warning, TEXT("Number of element %d "), InventoryListItems.Num());

}

void ATGCOPlayerState::RemoveInventoryItem(AStockable* _item)
{
	check(_item);
	InventoryListItems.Remove(_item);
}

TArray<AStockable*> ATGCOPlayerState::GetInventoryListItems()
{
	return InventoryListItems;
}

void ATGCOPlayerState::SetPropsAffected(AProps* PropsAffected)
{
	if (PropsAffectedByTime != nullptr)
	{
		PropsAffectedByTime->ReinitSpeedToInitialSpeed();
	}
	PropsAffectedByTime = PropsAffected;
}

bool ATGCOPlayerState::IsPropsAffected()
{
	return PropsAffectedByTime != nullptr;
}

EShootMode::Type ATGCOPlayerState::GetModUsed()
{
	return ModUsedOnProps;
}

void ATGCOPlayerState::SetModUsed(EShootMode::Type _mod)
{
	ModUsedOnProps = _mod;
}

void ATGCOPlayerState::EnterInAPuzzle()
{
	bIsInPuzzle = true;
}

void ATGCOPlayerState::LeaveAPuzzle()
{
	bIsInPuzzle = false;
}

bool ATGCOPlayerState::IsInPuzzle()
{
	return bIsInPuzzle;
}
