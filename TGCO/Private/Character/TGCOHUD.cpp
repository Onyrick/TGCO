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
	//Use the RobotoDistanceField font from the engine
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Game/Character/HUD/HUDFont"));
	HUDFont = HUDFontOb.Object;

	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/Textures/Crosshair"));
	CrosshairTex = CrosshiarTexObj.Object;
}

void ATGCOHUD::DrawHUD()
{
	//Get the screen dimensions
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

	Super::DrawHUD();

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

	ATGCOCharacter* Character = Cast<ATGCOCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (Character != nullptr)
	{
		FString ShootModeString = GetNameOfTheMode(Character->GetWristMode());
		DrawText(ShootModeString, FColor::White, 0, 50, HUDFont);
	}
}
