

#include "TGCO.h"
#include "InteractiveElement/OpenBarrierConsole.h"
#include "CodeBarrierDisplayer.h"
#include "Net/UnrealNetwork.h"

ACodeBarrierDisplayer::ACodeBarrierDisplayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	CodeToDisplay("666")
{

}

bool ACodeBarrierDisplayer::OnInteract()
{
	/**When the user interact with the displayer it sends a custom event so that its
	associated widget shows the code to the user (done in BP)*/
	CodeReadyToDisplay.Broadcast();
	return true;
}


void ACodeBarrierDisplayer::SetCodeToDisplay(FString code)
{
	CodeToDisplay = code;
	codeinstring = std::string(TCHAR_TO_UTF8(*code));

	//UE_LOG(LogDebug, Warning, TEXT("%s : Is the new code"), *code);
}


void ACodeBarrierDisplayer::SendCodeReadyEvent()
{
	CodeReadyToDisplay.Broadcast();
}

void ACodeBarrierDisplayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	/** Method used for replication purpose (synchronization client - server) */
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(ACodeBarrierDisplayer, CodeReadyToDisplay);
}