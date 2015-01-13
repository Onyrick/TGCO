// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CharacterAI.generated.h"

/**
 * TODO
 */
UCLASS()
class TGCO_API ACharacterAI : public ACharacter
{
	GENERATED_BODY()
public:
	/** Constructors */
	ACharacterAI(const FObjectInitializer& PCIP);

	/** Function to get the AIController */
	UFUNCTION(BlueprintCallable, Category = "CharacterAI")
	virtual AAIController* GetAIController();
	
	/** Event launch when the CharacterAI has to be destroyed */
	UFUNCTION(BlueprintCallable, Category = "CharacterAI")
	virtual void Destroy();

	/** Event launch when the CharacterAI take damage */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	/** Event launch when the CharacterAI is hit by another actor */
	virtual void ReceiveActorBeginOverlap(AActor* OtherActor) override;
	
	/** TODO */
	UPROPERTY(EditAnywhere, Category = "Static Meshes")
	UStaticMeshComponent* StaticMesh;
};