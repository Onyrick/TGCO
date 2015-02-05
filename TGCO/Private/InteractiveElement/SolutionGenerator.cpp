// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "SolutionGenerator.h"

ASolutionGenerator::ASolutionGenerator(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	SolutionType = ESolutionType::ACID;
}

bool ASolutionGenerator::OnInteract()
{
	//TODO
	UE_LOG(LogTest, Warning, TEXT("Solution Generator activate"));
	return true;
}
