

#include "TGCO.h"
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
}

void ARainbowBoxHandlerPast::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(ARainbowBoxHandlerPast, Squares);
}

void ARainbowBoxHandlerPast::CreateRainbowBoxHandler()
{
	//srand(time(NULL));
	srand(10);
	UE_LOG(LogTest, Warning, TEXT("In past"));

	//Create all the RainbowBox and set a random color between red, blue and green
	for (int i = 0; i < SIZE; ++i)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			//int iAddrandom = rand() % 6;
			int iAddrandom = 10;
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
					UE_LOG(LogTest, Warning, TEXT("RainbowBox %i is RED"), i);
					break;
				case 2:
					RainbowBox->SetColor(ERainbowBoxColor::BLUE);
					UE_LOG(LogTest, Warning, TEXT("RainbowBox %i is RED"), i);
					break;
				default:
					RainbowBox->SetColor(ERainbowBoxColor::NONE);
					UE_LOG(LogTest, Warning, TEXT("RainbowBox %i is RED"), i);
					break;
				}
				RainbowBox->SetShouldNotify(true);
				Squares.Add(RainbowBox);
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

/** Delete the array that contains ARainbowBox */
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
