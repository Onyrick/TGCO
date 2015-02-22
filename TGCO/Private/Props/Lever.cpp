// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "Lever.h"

ALever::ALever(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> LeverShape(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Lamp_Wall.SM_Lamp_Wall'"));
	StaticMeshProps->SetStaticMesh(LeverShape.Object);
}
