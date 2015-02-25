#include "TGCO.h"
#include "ConsoleMinesweeperUMG.h"

UConsoleMinesweeperUMG::UConsoleMinesweeperUMG(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UConsoleMinesweeperUMG::CreateConsoleMinesweeperUMG()
{
	/*if (Role < ROLE_Authority)
	{
		UE_LOG(LogTest, Warning, TEXT("CreateConsoleMinesweeperUMG : Pas autorité"));
	}
	else
	{
		UE_LOG(LogTest, Warning, TEXT("CreateConsoleMinesweeperUMG :Autorité"));
	}*/
}

bool UConsoleMinesweeperUMG::ServerCreateConsoleMinesweeperUMG_Validate()
{
	return true;
}

void UConsoleMinesweeperUMG::ServerCreateConsoleMinesweeperUMG_Implementation()
{
	UE_LOG(LogTest, Warning, TEXT("Je suis dans CreateConsoleMinesweeperUMG"));
	CreateConsoleMinesweeperUMG();
}
