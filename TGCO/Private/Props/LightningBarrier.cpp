
#include "TGCO.h"
#include "TGCOPlayerController.h"
#include "LightningBarrier.h"
#include "Puzzle/BarrierColor.h"
#include "Net/UnrealNetwork.h"


ALightningBarrier::ALightningBarrier(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),
	bIsLightningActive(true),
	bInMotion(false),
	fLength(250),
	rRotation(0.0f, 0.0f, 0.0f),
	pFutureBarrier(nullptr)
{
	fInitialSpeed = 0;
	/*Creation of the skeletal mesh that will visually represent the barrier*/
	pBarrier = ObjectInitializer.CreateDefaultSubobject<ULightningBarrierSkeletalMeshComp>(this, TEXT("Barrier"));
	pBarrier->AttachTo(StaticMeshProps);
	
	/*Component used to control the rotation of the barrier (used if the barrier is defined as a rotating one)*/
	RotatingMovement = ObjectInitializer.CreateDefaultSubobject<URotatingMovementComponent>(this, TEXT("RotatingMovement"));
	RotatingMovement->PivotTranslation = FVector(0, 0, 0);
	RotatingMovement->SetUpdatedComponent(pBarrier);
	RotatingMovement->RotationRate = fInitialSpeed *rRotation;
	
	/*Meshes representing the rails on which the barrier will be sliding if it has been defined as a translating one*/
	rail1 = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Rail1Barrier"));
	rail2 = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Rail2Barrier"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> shape(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Trim.Shape_Trim'"));
	railshape = shape.Object;
	ActivateInMotionCheckBox = 0;
	rail1->SetStaticMesh(railshape);
	rail1->AttachTo(pBarrier);
	rail1->SetVisibility(true, true);
	rail2->SetStaticMesh(railshape);
	rail2->AttachTo(pBarrier);
	rail2->SetVisibility(true, true);

	rail1->SetWorldRotation(FRotator(0, 90.0f, 0.00));
	rail2->SetWorldRotation(FRotator(0, 90.0f, 0.00));
	
	/*used for a feature still in development (being able to know which barrier is selected during the edition phase)*/
	USelection::SelectionChangedEvent.AddUObject(this, &ALightningBarrier::OnActorSelectionChanged);
	/*Set the barrier's default color */
	eBarColor = EBarrierColor::VE_Green;
}

void ALightningBarrier::OnActorSelectionChanged(UObject* obj)
{

}


void ALightningBarrier::BeginPlay()
{
	pBarrier->SetBarrierMaterial(eBarColor);
}


void ALightningBarrier::ChangeActiveState()
{
	/*The management of the change is different whether we are the client or the server */
	if (Role < ROLE_Authority)
	{
		/*In case of the client. It sends a request to the server so that the server apply the changes on its own and
		cascade down the changes back to the client*/
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerChangeActiveStateOnBarrier(this, !bIsLightningActive);
			if (pFutureBarrier != nullptr)
			{
				PC->ServerChangeActiveStateOnBarrier(pFutureBarrier, !bIsLightningActive);
			}
		}
	}
	else
	{
		/*In case of the server*/
		bIsLightningActive = !bIsLightningActive;
		UpdateActiveState();
		if (pFutureBarrier != nullptr)
		{
			pFutureBarrier->SetActiveState(bIsLightningActive);
		}
	}
}

void ALightningBarrier::SetActiveState(bool state)
{
	bIsLightningActive = state;
	UpdateActiveState();
}

void ALightningBarrier::ChangeActiveStateFromServer(bool bValue)
{
	bIsLightningActive = bValue;
	UpdateActiveState();
}

void ALightningBarrier::OnRep_LightningState()
{
	UpdateActiveState();
}

void ALightningBarrier::UpdateActiveState()
{
	if (pBarrier != nullptr)
	{
		pBarrier->ChangeLightningState(bIsLightningActive);
		if (Role < ROLE_Authority)
		{
			pBarrier->ChangeLightningState(bIsLightningActive);
		}
	}
}

/*Method used for edition purpose. It allows the designer to hone the instance of the object in the editor to its convenience
Each property can be tweaked to fit the designer needs*/
void ALightningBarrier::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if ((PropertyName == GET_MEMBER_NAME_CHECKED(ALightningBarrier, bIsLightningActive)) && pBarrier != nullptr)
	{
		pBarrier->ChangeLightningState(bIsLightningActive);
	}
	/* Check if the property change event is applied to the array*/
	else if ((PropertyName == GET_MEMBER_NAME_CHECKED(ALightningBarrier, eDirection)))
	{
		ActivateInMotionCheckBox = 1;
		switch (eDirection)
		{
		case EMotionDir::VE_None:
			ActivateInMotionCheckBox = 0;
			break;
		case EMotionDir::VE_X_Axis:
			bInMotion = false;
			vMotion = FVector(1.0, 0.0, 0.0);
			break;
		case EMotionDir::VE_Y_Axis:
			vMotion = FVector(0.0, 1.0, 0.0);
			break;
		case EMotionDir::VE_Z_Axis:
			vMotion = FVector(0.0, 0.0, 1.0);
			break;
		case EMotionDir::VE_RY_Axis:
			rRotation = FRotator(0, 1.0f, 0);
			break;
		case EMotionDir::VE_RZ_Axis:
			rRotation = FRotator(0, 0, 1.0f);
			break;
		default:
			break;
		}
		auto transVector = fLength * vMotion;
		RotatingMovement->RotationRate = fInitialSpeed *rRotation;
	}
	/*Rotation speed modifications*/
	else if ((PropertyName == GET_MEMBER_NAME_CHECKED(ALightningBarrier, fInitialSpeed)))
	{
		RotatingMovement->RotationRate = fInitialSpeed *rRotation;
	}
	/*Update of the rails lenght*/
	else if ((PropertyName == GET_MEMBER_NAME_CHECKED(ALightningBarrier, fLength)))
	{
		auto bound = railshape->GetBounds();
		rail1->SetWorldScale3D(FVector(1.f, fLength / bound.BoxExtent.Y, 1.0f));
		rail2->SetWorldScale3D(FVector(1.f, fLength / bound.BoxExtent.Y, 1.0f));
		bound = rail1->Bounds;
		rail1->SetWorldLocation(this->GetActorLocation() + FVector(bound.BoxExtent.X, 0, 0));
		bound = rail2->Bounds;
		rail2->SetWorldLocation(pBarrier->pSecondTerminalComponent->GetComponentLocation() + FVector(bound.BoxExtent.X, 0, 0));
	}
	/*On the check of the checkbox defining that the barrier is a moving one, gives acces to more options in the editor*/
	else if ((PropertyName == GET_MEMBER_NAME_CHECKED(ALightningBarrier, ActivateInMotionCheckBox)))
	{
		if (ActivateInMotionCheckBox != 0)
		{
			if (rail1 != nullptr)
			{
				rail1->SetStaticMesh(railshape);
				rail1->SetWorldRotation(FRotator(0, 90, 0));
				rail1->SetWorldScale3D(FVector(1.f, 5.f, 1.0f));
				auto bound = rail1->Bounds;
				rail1->SetWorldLocation(this->GetActorLocation() + FVector(bound.BoxExtent.X, 0, 0));
			}
			if (rail2 != nullptr)
			{
				rail2->SetStaticMesh(railshape);
				rail2->SetWorldRotation(FRotator(0, 90, 0));
				rail2->SetWorldScale3D(FVector(1.f, 5.f, 1.0f));
				auto bound = rail2->Bounds;
				rail2->SetWorldLocation(pBarrier->pSecondTerminalComponent->GetComponentLocation() + FVector(bound.BoxExtent.X, 0, 0));
			}
		}
		else
		{
			rail1->SetStaticMesh(nullptr);
			rail2->SetStaticMesh(nullptr);
		}
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void ALightningBarrier::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(ALightningBarrier, bIsLightningActive);
}
