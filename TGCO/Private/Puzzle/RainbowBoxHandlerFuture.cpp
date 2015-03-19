
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
	Handler = TArray< ARainbowBox* >();
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
		iSize = iColumns * iRows;
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			ATGCOGameState* GameState = Cast<ATGCOGameState>(World->GetGameState());
			if (GameState)
			{
				srand(time(nullptr));

				//Create all the RainbowBox and set a random color between red, blue and green
				for (int x = 0; x < iColumns; ++x)
				{
					for (int y = 0; y < iRows; ++y)
					{
						int iAddrandom = rand() % 6;
						// Make some holes when random is 0
						if (iAddrandom > 0)
						{
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
							Handler.Add(RainbowBox);
						}
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
	Handler.Empty();
}

void ARainbowBoxHandlerFuture::HideAllOfThisColor(ERainbowBoxColor::Color HideColor)
{
	for (int i = 0; i < Handler.Num(); ++i)
	{
		ARainbowBox* RainbowBox = Handler[i];
		if (GetNameOfTheColor(RainbowBox->GetColor()).IsEqual(GetNameOfTheColor(HideColor)))
		{
			RainbowBox->Hide();
			RainbowBox->SetIsHideInPast(true);
		}
		else
		{
			RainbowBox->SetIsHideInPast(false);
			if (	MustStayRainbowBox != nullptr &&
					GetNameOfTheColor(MustStayRainbowBox->GetColor()).IsEqual(GetNameOfTheColor(RainbowBox->GetColor())) &&
					!(RainbowBox->GetActorLocation() == MustStayRainbowBox->GetActorLocation())
				)
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

void ARainbowBoxHandlerFuture::HideAllExcepted(ARainbowBox* StayRainbowBox)
{
	MustStayRainbowBox = StayRainbowBox;
	for (int i = 0; i < Handler.Num(); ++i)
	{

		ARainbowBox* RainbowBox = Handler[i];
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
