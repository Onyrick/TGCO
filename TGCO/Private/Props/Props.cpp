

#include "TGCO.h"
#include "Props.h"


AProps::AProps(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	StaticMeshProps = PCIP.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("StaticMesh_InteractiveElement"));
	
	RootComponent = StaticMeshProps;

}

UStaticMeshComponent* AProps::getStaticMesh()
{
	return StaticMeshProps;
}