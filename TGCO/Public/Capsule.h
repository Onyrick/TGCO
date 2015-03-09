

#pragma once

#include "Stockable/Stockable.h"
#include "SolutionType.h"
#include "Capsule.generated.h"


UCLASS()
class TGCO_API ACapsule : public AStockable
{
	GENERATED_BODY()
	
public:
	ACapsule(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Capsule")
	TEnumAsByte<ESolutionType::Type> SolutionType;

	UFUNCTION(BlueprintCallable, Category = "Capsule")
	TEnumAsByte<ESolutionType::Type> GetSolutionType();
};
