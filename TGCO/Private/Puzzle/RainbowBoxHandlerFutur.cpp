
#include "TGCO.h"
#include "Net/UnrealNetwork.h"
#include "RainbowBoxHandlerFutur.h"

ARainbowBoxHandlerFutur::ARainbowBoxHandlerFutur(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<ARainbowBox> ItemBlueprint(TEXT("/Game/Blueprints/RainbowBox_BP"));
	if (ItemBlueprint.Class != NULL)
	{
		RainbowBoxBP = (UClass*)ItemBlueprint.Class;
	}
	Squares = TArray< ARainbowBox* >();
	MustStayRainbowBox = nullptr;
}

/*void ARainbowBoxHandlerFutur::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(ARainbowBoxHandlerFutur, Squares);
}*/

void ARainbowBoxHandlerFutur::CreateRainbowBoxHandler()
{
	//srand(time(NULL));
	srand(12);

	UE_LOG(LogTest, Warning, TEXT("In futur"));
	//Create all the RainbowBox and set a random color between red, blue and green
	for (int i = 0; i < SIZE; ++i)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
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
					break;
				}
				RainbowBox->Hide();
				Squares.Add(RainbowBox);
			}
		}
	}
}

bool ARainbowBoxHandlerFutur::ServerCreateRainbowBoxHandler_Validate()
{
	return true;
}

void ARainbowBoxHandlerFutur::ServerCreateRainbowBoxHandler_Implementation()
{
	CreateRainbowBoxHandler();
}

/** Delete the array that contains ARainbowBox */
void ARainbowBoxHandlerFutur::DeleteRainbow()
{
	Squares.Empty();
}

void ARainbowBoxHandlerFutur::HideAllOfThisColor(ERainbowBoxColor::Color HideColor)
{
	for (int i = 0; i < Squares.Num(); ++i)
	{
		ARainbowBox* RainbowBox = Squares[i];
		if (GetNameOfTheColor(RainbowBox->GetColor()).IsEqual(GetNameOfTheColor(HideColor)))
		{
			RainbowBox->Hide();
			RainbowBox->SetIsHideInPast(true);
		}
		else
		{

			RainbowBox->SetIsHideInPast(false);
			if (MustStayRainbowBox != nullptr)
			{
				if (GetNameOfTheColor(MustStayRainbowBox->GetColor()).IsEqual(GetNameOfTheColor(RainbowBox->GetColor())))
				{

					if (!(RainbowBox->GetActorLocation() == MustStayRainbowBox->GetActorLocation()))
					{
						RainbowBox->Hide();
					}
					else
					{
						RainbowBox->Show();
					}
				}
				else
				{
					RainbowBox->Show();
				}
			}
			else
			{
				RainbowBox->Show();
			}
		}
	}
}

void ARainbowBoxHandlerFutur::HideAllExcepted(ARainbowBox* StayRainbowBox)
{
	MustStayRainbowBox = StayRainbowBox;
	for (int i = 0; i < Squares.Num(); ++i)
	{

		ARainbowBox* RainbowBox = Squares[i];
		if (GetNameOfTheColor(RainbowBox->GetColor()).IsEqual(GetNameOfTheColor(StayRainbowBox->GetColor())))
		{
			if (! (RainbowBox == StayRainbowBox) )
			{
				RainbowBox->Hide();
			}
		}
		else
		{
			if (RainbowBox->GetIsHideInPast())
			{
				RainbowBox->Hide();
			}
			else
			{
				RainbowBox->Show();
			}
		}
	}
}

