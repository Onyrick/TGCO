
#include "TGCO.h"
#include "TGCOGameState.h"
#include "Net/UnrealNetwork.h"
#include "RainbowBoxHandlerFuture.h"

ARainbowBoxHandlerFuture::ARainbowBoxHandlerFuture(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, MustStayRainbowBox(nullptr)
{
	static ConstructorHelpers::FClassFinder<ARainbowBox> ItemBlueprint(TEXT("/Game/Blueprints/RainbowBox_BP"));
	if (ItemBlueprint.Class != nullptr)
	{
		RainbowBoxBP = (UClass*)ItemBlueprint.Class;
	}
	Squares = TArray< ARainbowBox* >();
	bReplicates = true;
}

void ARainbowBoxHandlerFuture::CreateRainbowBoxHandler()
{
	if (Role < ROLE_Authority)
	{
		ServerCreateRainbowBoxHandler();
	}
	else
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			ATGCOGameState* GameState = Cast<ATGCOGameState>(World->GetGameState());
			if (GameState)
			{
				srand(time(nullptr));

				//Create all the RainbowBox and set a random color between red, blue and green
				// TODO : make it works with NB_COL != NB_ROW, make size blueprint editable
				for (int i = 0; i < SIZE; ++i)
				{
					// TODO : Check this random, make it FMath::RandRange(min, max) ?
					int iAddrandom = rand() % 6;
					// Make some holes when random is 0
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
							break;
						case 1:
							RainbowBox->SetColor(ERainbowBoxColor::GREEN);
							break;
						case 2:
							RainbowBox->SetColor(ERainbowBoxColor::BLUE);
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
	}
}

bool ARainbowBoxHandlerFuture::ServerCreateRainbowBoxHandler_Validate()
{
	return true;
}

void ARainbowBoxHandlerFuture::ServerCreateRainbowBoxHandler_Implementation()
{
	CreateRainbowBoxHandler();
}

void ARainbowBoxHandlerFuture::DeleteRainbow()
{
	Squares.Empty();
}

void ARainbowBoxHandlerFuture::HideAllOfThisColor(ERainbowBoxColor::Color HideColor)
{
	// TODO : check if some "else" should be remove
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

void ARainbowBoxHandlerFuture::HideAllExcepted(ARainbowBox* StayRainbowBox)
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
