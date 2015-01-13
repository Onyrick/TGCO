

#include "TGCO.h"
#include "Lever.h"


ALever::ALever(const FObjectInitializer& PCIP)
	:Super(PCIP)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> LeverShape(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Lamp_Wall.SM_Lamp_Wall'"));
	StaticMeshProps->SetStaticMesh(LeverShape.Object);
}


