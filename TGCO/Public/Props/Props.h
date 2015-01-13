

#pragma once

#include "GameFramework/Actor.h"
#include "Props.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API AProps : public AActor
{
	GENERATED_BODY()
	
public:
	//Constructors
	AProps(const FObjectInitializer& PCIP);

	//UPROPERTY(EditAnywhere, Category = "Triggers")
	//	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, Category = "PropsComponents")
		UStaticMeshComponent* StaticMeshProps;
	
	virtual UStaticMeshComponent* getStaticMesh();
};
