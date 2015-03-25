
#include "TGCO.h"
#include "TGCOPlayerController.h"
#include "LightningBarrier.h"
#include "Puzzle/BarrierColor.h"
#include "Net/UnrealNetwork.h"


ALightningBarrier::ALightningBarrier(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer),
	bIsLightningActive(true),
	fPercentageWayCovered(0.0),
	bInMotion(false),
	bCompleted(false),
	fLength(250),
	rRotation(0.0f, 0.0f, 0.0f)
{
	fInitialSpeed = 0;
	pBarrier = ObjectInitializer.CreateDefaultSubobject<ULightningBarrierSkeletalMeshComp>(this, TEXT("Barrier"));
	pBarrier->AttachTo(StaticMeshProps);

	RotatingMovement = ObjectInitializer.CreateDefaultSubobject<URotatingMovementComponent>(this, TEXT("RotatingMovement"));
	RotatingMovement->PivotTranslation = FVector(0, 0, 0);
	RotatingMovement->SetUpdatedComponent(pBarrier);
	RotatingMovement->RotationRate = fInitialSpeed *rRotation;
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
	
///	pBarrier->SetBarrierMaterial(eBarColor);
	USelection::SelectionChangedEvent.AddUObject(this, &ALightningBarrier::OnActorSelectionChanged);
	eBarColor = EBarrierColor::VE_Green;
}

void ALightningBarrier::OnActorSelectionChanged(UObject* obj)
{

}


void ALightningBarrier::BeginPlay()
{
	//pBarrier->SetBarrierMaterial(eColor);
}


void ALightningBarrier::ChangeActiveState()
{
	if (Role < ROLE_Authority)
	{
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerChangeActiveStateOnBarrier(this, !bIsLightningActive);
		}
	}
	else
	{
		bIsLightningActive = !bIsLightningActive;
		UpdateActiveState();
	}
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
	else if ((PropertyName == GET_MEMBER_NAME_CHECKED(ALightningBarrier, fInitialSpeed)))
	{
		RotatingMovement->RotationRate = fInitialSpeed *rRotation;
	}

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
