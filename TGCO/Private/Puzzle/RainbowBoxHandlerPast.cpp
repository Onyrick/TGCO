

#include "TGCO.h"
#include "TGCOGameState.h"
#include "Net/UnrealNetwork.h"
#include "RainbowBoxHandlerPast.h"

ARainbowBoxHandlerPast::ARainbowBoxHandlerPast(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<ARainbowBox> ItemBlueprint(TEXT("/Game/Blueprints/RainbowBox_BP"));
	if (ItemBlueprint.Class != NULL)
	{
		RainbowBoxBP = (UClass*)ItemBlueprint.Class;
	}
	Squares = TArray< ARainbowBox* >();
	bReplicates = true;
}

void ARainbowBoxHandlerPast::CreateRainbowBoxHandler()
{
	if (Role < ROLE_Authority)
	{
		ServerCreateRainbowBoxHandler();
	}
	else
	{
		UE_LOG(LogTest, Warning, TEXT("In past"));

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			ATGCOGameState* GameState = Cast<ATGCOGameState>(World->GetGameState());
			if (GameState)
			{
				srand(time(NULL));
				
				//Create all the RainbowBox and set a random color between red, blue and green
				for (int i = 0; i < SIZE; ++i)
				{
					int iAddrandom = rand() % 6;
					if (iAddrandom > 0)
					{
						unsigned int x = i / NB_COL;
						unsigned int y = i % NB_COL;
						const FVector SpawnLocation = GetActorLocation() + FVector(x * 480, y * 480, 5.0);
						const FRotator SpawnRotation = GetActorRotation();
						ARainbowBox* RainbowBox = (ARainbowBox*)World->SpawnActor<ARainbowBox>(RainbowBoxBP, SpawnLocation, SpawnRotation);

						int iColorRandom = rand() % 3;
						switch (iColorRandom)
						{
						case 0:
							RainbowBox->SetColor(ERainbowBoxColor::RED);
							UE_LOG(LogTest, Warning, TEXT("RainbowBox %i is RED"), i);
							break;
						case 1:
							RainbowBox->SetColor(ERainbowBoxColor::GREEN);
							UE_LOG(LogTest, Warning, TEXT("RainbowBox %i is GREEN"), i);
							break;
						case 2:
							RainbowBox->SetColor(ERainbowBoxColor::BLUE);
							UE_LOG(LogTest, Warning, TEXT("RainbowBox %i is BLUE"), i);
							break;
						default:
							RainbowBox->SetColor(ERainbowBoxColor::NONE);
							UE_LOG(LogTest, Warning, TEXT("RainbowBox %i is NONE"), i);
							break;
						}
						RainbowBox->SetShouldNotify(true);
						Squares.Add(RainbowBox);
					}
				}
			}

		}
	}
}

bool ARainbowBoxHandlerPast::ServerCreateRainbowBoxHandler_Validate()
{
	return true;
}

void ARainbowBoxHandlerPast::ServerCreateRainbowBoxHandler_Implementation()
{
	CreateRainbowBoxHandler();
}

void ARainbowBoxHandlerPast::DeleteRainbow()
{
	Squares.Empty();
}

void ARainbowBoxHandlerPast::HideAllExcepted(ARainbowBox* StayRainbowBox)
{
	
	for (int i = 0; i < Squares.Num(); ++i)
	{
		ARainbowBox* RainbowBox = Squares[i];
		if (GetNameOfTheColor(RainbowBox->GetColor()).IsEqual(GetNameOfTheColor(StayRainbowBox->GetColor())))
		{
			if (!(RainbowBox->GetActorLocation() == StayRainbowBox->GetActorLocation()))
			{
				RainbowBox->Hide();
			}
		}
		else
		{
			RainbowBox->Show();
		}
	}
}
