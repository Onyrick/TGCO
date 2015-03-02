// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "ShootMode.h"

int GetEnergyConsuming(const EShootMode::Type ShootMode)
{
	switch (ShootMode)
	{
		case EShootMode::SLOW:					return 20;
		case EShootMode::SPEED:					return 15;
		case EShootMode::STOP:					return 40;
		default:								return 0;
	}

}

FString GetNameOfTheMode(const EShootMode::Type ShootMode)
{
	switch (ShootMode)
	{
		case EShootMode::SLOW:					return FString(TEXT("Slow"));
		case EShootMode::SPEED:					return FString(TEXT("Speed"));
		case EShootMode::STOP:					return FString(TEXT("Stop"));
		default:								return FString(TEXT("Unknown"));
	}

}