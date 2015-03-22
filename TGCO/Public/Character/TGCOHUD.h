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
	
	/** @brief	The material for the mouse cursor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
	UMaterial* MouseCursorMaterial;

	/**
	* @brief	Gets HUD energy umg.
	*
	* @return	null if it fails, else the HUD energy umg.
	*/
	UFUNCTION(BlueprintCallable, Category = "HUD")
	UUserWidget* GetHUDEnergyUMG() const;

	/**
	* @brief	Sets HUD energy umg.
	*
	* @param 	_widget	If non-null, the widget.
	*/
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetHUDEnergyUMG(UUserWidget* _widget);

	/** @brief Change the visibility of the HUD */
	void SetHUDVisibility(bool _visible);

protected:
	/** @brief	The HUD of the player with energy and shoot mode umg. */
	UUserWidget* HUDEnergyUMG;

private:
	/** @brief  Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};
