
#pragma once

#include "Props/Props.h"
#include "Tree.generated.h"

/**
 * @class UTree
 * 		  
 * @brief Class that defines a tree. It's a static mesh component that can be add in actor.
 */
UCLASS()
class TGCO_API UTree : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTree(const FObjectInitializer& ObjectInitializer);
		
};
