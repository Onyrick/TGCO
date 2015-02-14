
#include "TGCO.h"
#include "RainbowBoxHandlerFutur.h"

ARainbowBoxHandlerFutur::ARainbowBoxHandlerFutur(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<ARainbowBox> ItemBlueprint(TEXT("/Game/Blueprints/RainbowBox_BP"));
	if (ItemBlueprint.Class != NULL)
	{
		RainbowBoxBP = (UClass*)ItemBlueprint.Class;
	}
}

void ARainbowBoxHandlerFutur::CreateRainbowBoxHandler()
{
	srand(time(NULL));

	//Create all the RainbowBox and set a random color between red, blue and green
	for (int i = 0; i < SIZE; ++i)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			unsigned int x = i / NB_COL;
			unsigned int y = i % NB_COL;
			const FVector SpawnLocation = GetActorLocation() + FVector(x * 405, y * 405, 5.0);
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

/** Delete the array that contains ARainbowBox */
void ARainbowBoxHandlerFutur::DeleteRainbow()
{
	Squares.Empty();
}

void ARainbowBoxHandlerFutur::HideAllExcepted(ERainbowBoxColor::Color StayColor)
{
	for (int i = 0; i < SIZE; ++i)
	{

		ARainbowBox* RainbowBox = Squares[i];
		if (GetNameOfTheColor(RainbowBox->GetColor()).IsEqual(GetNameOfTheColor(StayColor)))
		{
			RainbowBox->Hide();
		}
		else
		{
			RainbowBox->Show();
		}
	}
}

