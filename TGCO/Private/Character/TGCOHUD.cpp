// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOHUD.h"
#include "TGCOCharacter.h"
#include "TGCOPlayerController.h"

#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

ATGCOHUD::ATGCOHUD(const FObjectInitializer& ObjectInitializer) 
: Super(ObjectInitializer)
, MouseCursorMaterial(nullptr)
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

	UE_LOG(LogDebug, Warning, TEXT("Draw hud true !"));
	
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
		else if (PlayerState != nullptr)
		{
			// Draw a custom mouse cursor 
			float fMouseCursorX, fMouseCursorY;
			bool succes = PlayerController->GetMousePosition(fMouseCursorX, fMouseCursorY);
			int iViewportSizeX, iViewportSizeY;
			PlayerController->GetViewportSize(iViewportSizeX, iViewportSizeY);

			float literalFloat = 32.f;

			float newMousePosX = static_cast<float>(ScreenDimensions.X - iViewportSizeX) / 2.0f + fMouseCursorX - (literalFloat / 2.0f);
			float newMousePosY = static_cast<float>(ScreenDimensions.Y - iViewportSizeY) / 2.0f + fMouseCursorY - (literalFloat / 2.0f);

			if (MouseCursorMaterial != nullptr)
			{
				DrawMaterial(MouseCursorMaterial, newMousePosX, newMousePosY, literalFloat, literalFloat, 0.0f, 0.0f, 1.0f, 1.0f);
			}
		}
	}
}

UUserWidget* ATGCOHUD::GetHUDEnergyUMG() const
{
	return HUDEnergyUMG;
}

void ATGCOHUD::SetHUDEnergyUMG(UUserWidget* _widget)
{
	check(_widget);
	HUDEnergyUMG = _widget;
}

void ATGCOHUD::SetHUDVisibility(bool _visible)
{
	if (_visible)
	{
		HUDEnergyUMG->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogOnline, Log, TEXT("Change HUD to be visible"));
	}
	else
	{
		HUDEnergyUMG->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogOnline, Log, TEXT("Change HUD to be hidden"));
	}
}
