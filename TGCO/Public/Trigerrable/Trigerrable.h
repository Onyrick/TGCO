#pragma once

#include "GameFramework/Actor.h"
#include "Trigerrable.generated.h"

UCLASS()
class TGCO_API ATrigerrable : public AActor
{
	GENERATED_BODY()
public:
	//Constructors
	ATrigerrable(const FObjectInitializer& PCIP);

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Event launch when Player trigger the component.
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION()
		virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Event launch when Player trigger the component.
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION()
		virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere, Category = "Triggers")
		UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent* StaticMesh;
};