

#pragma once

#include "GameFramework/PlayerController.h"
#include "TGCOPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API ATGCOPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

public:
	/** Set game in pause */
	virtual bool SetPause(bool bPause, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	virtual void SetupInputComponent() override;

private:
	void OnTogglePause();
};
