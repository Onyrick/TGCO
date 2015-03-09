// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "TGCOHUD.generated.h"

/**
 * A Simple HUD for Player
 * Display a crosshair on the screen
 */
UCLASS()
class TGCO_API ATGCOHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	/** Constructors */
	ATGCOHUD(const FObjectInitializer& ObjectInitializer);

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
	
};
