// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOHUD.h"
#include "TGCOCharacter.h"

#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

ATGCOHUD::ATGCOHUD(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/Textures/Crosshair"));
	CrosshairTex = CrosshiarTexObj.Object;
}


void ATGCOHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair if Player is in Shoot Mode
	// Get the player 
	ATGCOCharacter* MyCharacter = Cast<ATGCOCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		if (MyCharacter->bShootMode)
		{
			// find center of the Canvas
			const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

			// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
			const FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
				(Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));

			// draw the crosshair
			FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
			TileItem.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(TileItem);
		}
	}
}

