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
		UE_LOG(LogTest, Warning, TEXT("CreateConsoleMinesweeperUMG : Pas autorit�"));
	}
	else
	{
		UE_LOG(LogTest, Warning, TEXT("CreateConsoleMinesweeperUMG :Autorit�"));
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
