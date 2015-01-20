#pragma once

//#include "GameFramework/TargetPoint.h"
#include "BotTargetPoint.generated.h"

UCLASS()
class TGCO_API ABotTargetPoint : public ATargetPoint
{
	GENERATED_UCLASS_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Id Target Point")
	int32 iIDTargetPoint;

};