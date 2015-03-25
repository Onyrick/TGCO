
#include "TGCO.h"
#include "TGCOHUD.h"
#include "TGCOCharacter.h"
#include "TGCOPlayerController.h"

#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

ATGCOHUD::ATGCOHUD(const FObjectInitializer& ObjectInitializer) 
: Super(ObjectInitializer)
{
	//Use the RobotoDistanceField font from the engine
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Game/Character/HUD/HUDFont"));
	HUDFont = HUDFontOb.Object;

	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/Textures/Crosshair"));
	CrosshairTex = CrosshiarTexObj.Object;
}

void ATGCOHUD::DrawHUD()
{
	Super::DrawHUD();
	
	ATGCOPlayerController* PlayerController = Cast<ATGCOPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController != nullptr)
	{
		//Get the screen dimensions
		FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

		ATGCOPlayerState * PlayerState = Cast<ATGCOPlayerState>(PlayerController->PlayerState);
		if (PlayerState != nullptr && PlayerState->eCurrentState == EPlayerStatus::IN_GAME)
		{
			// Draw very simple crosshair 
			// Find center of the Canvas
			const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

			// Offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
			const FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
				(Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));

			// Draw the crosshair
			FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
			TileItem.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(TileItem);
		}
	}
}

