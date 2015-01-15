// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Props.generated.h"

/**
 * TODO
 */
UCLASS()
class TGCO_API AProps : public AActor
{
	GENERATED_BODY()
	
public:
	/** Constructors */
	AProps(const FObjectInitializer& PCIP);

	//UPROPERTY(EditAnywhere, Category = "Triggers")
	//UBoxComponent* TriggerBox;
	
	/** TODO */
	virtual UStaticMeshComponent* getStaticMesh();

public: 
	/** TODO */
	UPROPERTY(EditAnywhere, Category = "PropsComponents")
	UStaticMeshComponent* StaticMeshProps;
};
