// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ControllerAI.h"
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
	ACharacterAI(const FObjectInitializer& ObjectInitializer);

	/** Function to get the AIController */
	UFUNCTION(BlueprintCallable, Category = "CharacterAI")
	virtual AControllerAI* GetAIController();
	
	/** Event launch when the CharacterAI has to be destroyed */
	UFUNCTION(BlueprintCallable, Category = "CharacterAI")
	virtual void Destroy();

	/** Event launch when the CharacterAI take damage */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	/** Event launch when the CharacterAI is hit by another actor */
	virtual void ReceiveActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, Category = "Static Meshes")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

	/** Function to make the character face a direction */
	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) override;

};
