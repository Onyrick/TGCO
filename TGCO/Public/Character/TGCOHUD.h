// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "TGCOHUD.generated.h"

UCLASS()
/** @brief	A Simple HUD for Player Display a crosshair and shoot mode on the screen. */
class TGCO_API ATGCOHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief	Constructor.
	 *
	 * @param	ObjectInitializer	The object initializer.
	 */
	ATGCOHUD(const FObjectInitializer& ObjectInitializer);

	/** @brief	Draw HUD. */
	virtual void DrawHUD() override;
	
	/** @brief   Variable for storing the font */
	UPROPERTY()
	class UFont* HUDFont;

private:
	/** @brief  Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
};
