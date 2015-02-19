
#pragma once

//#include "GameFramework/TargetPoint.h"
#include "BotTargetPoint.generated.h"

UCLASS()
class TGCO_API ABotTargetPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	ABotTargetPoint(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Id Target Point")
	int32 iIDTargetPoint;

};
