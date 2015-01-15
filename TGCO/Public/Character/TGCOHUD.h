// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "TGCOHUD.generated.h"

/**
 * TODO
 */
UCLASS()
class TGCO_API ATGCOHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ATGCOHUD(const FObjectInitializer& ObjectInitializer);

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
	
};
