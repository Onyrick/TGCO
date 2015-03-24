
#pragma once

#include "GameFramework/Actor.h"
#include "Stockable.h"
#include "DoorKey.generated.h"

/**
 * TODO
 */
UCLASS()
class TGCO_API ADoorKey : public AStockable
{
	GENERATED_BODY()

public:
	ADoorKey(const FObjectInitializer& ObjectInitializer);

};
