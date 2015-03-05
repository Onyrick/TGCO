

#pragma once

#include "GameFramework/PlayerController.h"
#include "ConsoleMinesweeper.h"
#include "TGCOPlayerController.generated.h"

class AProps;
class AFan;

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

	/** SERVER FUNCTIONS **/
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerUpdateSpeedOnProps(class AProps* Props);

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerUpdateSpeedValueOnProps(class AProps* Props, float fValue);

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerUpdateVisibilityOnMesh(class UStaticMeshComponent* Meshs);

	UFUNCTION(Client, Reliable)
	void ClientAffectSpeedOnFuturFan(class AFan* Fan, float _fSpeed);
	
protected:
	virtual void BeginPlay() override;
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	virtual void SetupInputComponent() override;

private:
	void OnTogglePause();
};
