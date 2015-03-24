
#include "TGCO.h"
#include "TGCOGameState.h"
#include "TGCOPlayerState.h"
#include "TGCOGameInstance.h"
#include "TGCOPlayerController.h"
#include "Net/UnrealNetwork.h"

ATGCOGameState::ATGCOGameState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, iPlayersEnergy(1000)
, iPlayersEnergyIncrement(10)
, iMaxPlayersEnergy(1000)
, fLastRegenTime(0.f)
, fRegenTime(0.1f)
, fResumeRegenAfterDecrease(2.5f)
{
	MapUnlockSkills.Add(0, EShootMode::STOP);
	MapUnlockSkills.Add(1, EShootMode::SLOW);
	MapUnlockSkills.Add(2, EShootMode::SPEED);
}

const TMap<int, EShootMode::Type>& ATGCOGameState::GetUnlockSkills()
{
	return MapUnlockSkills;
}

void ATGCOGameState::ManagePlayersEnergy()
{
	ATGCOPlayerState* PlayerState = Cast<ATGCOPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	if (PlayerState != nullptr)
	{
		if (PlayerState->GetModUsed() != EShootMode::NONE)
		{
			if (GetEnergy() == 1)
			{
				PlayerState->SetPropsAffected(NULL);
				PlayerState->SetModUsed(EShootMode::NONE);
			}
			else
			{
				DecreaseEnergy(GetEnergyConsuming(PlayerState->GetModUsed()));
			}
		}
		else
		{
			UpdateEnergy();
		}
	}
}

void ATGCOGameState::UpdateEnergy()
{
	float fGameTime = GetWorld()->GetTimeSeconds();
	if (fGameTime - fLastRegenTime >= fRegenTime)
	{
		AddEnergy(iPlayersEnergyIncrement);
		fLastRegenTime = fGameTime;
	}
	
}

void ATGCOGameState::AddEnergy(int32 iEnergyAmount)
{
	if (Role < ROLE_Authority)
	{
		ATGCOPlayerController * PC = Cast<ATGCOPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PC != nullptr)
		{
			PC->ServerAddEnergy(this, iEnergyAmount);
		}
	}
	else
	{
		iPlayersEnergy = FMath::Min(iMaxPlayersEnergy, iPlayersEnergy + iEnergyAmount);
	}
}

void ATGCOGameState::IncreaseEnergyMax(int32 iEnergyAmount)
{
	if (Role < ROLE_Authority)
	{
		ServerIncreaseEnergyMax(iEnergyAmount);
	}
	else
	{
		iMaxPlayersEnergy += iEnergyAmount;
	}
}

bool ATGCOGameState::ServerIncreaseEnergyMax_Validate(int32 iEnergyAmount)
{
	return true;
}

void ATGCOGameState::ServerIncreaseEnergyMax_Implementation(int32 iEnergyAmount)
{
	IncreaseEnergyMax(iEnergyAmount);
}

void ATGCOGameState::DecreaseEnergy(int32 iEnergyAmount, bool bCanPlayerDie)
{
	if (Role < ROLE_Authority)
	{
		ATGCOPlayerController * PC = Cast<ATGCOPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PC != nullptr)
		{
			PC->ServerDecreaseEnergy(this, iEnergyAmount, bCanPlayerDie);
		}
	}
	else
	{
		if (iEnergyAmount < 0)
		{
			iEnergyAmount = -iEnergyAmount;
		}

		iPlayersEnergy = FMath::Max(0, iPlayersEnergy - iEnergyAmount);

		if (iPlayersEnergy <= 0 && bCanPlayerDie == false)
		{
			iPlayersEnergy = 1;
		}

		fLastRegenTime = this->GetWorld()->GetTimeSeconds() + fResumeRegenAfterDecrease;
	}
}

bool ATGCOGameState::CheckRemainingEnergy()
{
	return iPlayersEnergy > 0;
}

void ATGCOGameState::MulticastRemoveAllWidgets_Implementation()
{
	UGameViewportClient* GVC = GEngine->GameViewport;
	if (GVC != nullptr)
	{
		GVC->RemoveAllViewportWidgets();
	}
}

void ATGCOGameState::MulticastGoToPlayingState_Implementation()
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		UTGCOGameInstance* GameInstance = Cast<UTGCOGameInstance>(World->GetGameInstance());
		if (GameInstance != nullptr)
		{
			GameInstance->SetCurrentState(FName(TEXT("Playing")));
		}
	}
}

void ATGCOGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(ATGCOGameState, iPlayersEnergy);
	DOREPLIFETIME(ATGCOGameState, iMaxPlayersEnergy);
}
