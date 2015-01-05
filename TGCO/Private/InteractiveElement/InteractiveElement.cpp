#include "TGCO.h"
#include "InteractiveElement.h"

UInteractiveElement::UInteractiveElement(const class FObjectInitializer& PCIP) : Super(PCIP)
{

}

void IInteractiveElement::OnInteract()
{
	unimplemented();
}

void IInteractiveElement::Highlight(bool highlight)
{
	//TODO
}

bool IInteractiveElement::IsInteractive()
{
	
	return bIsInteractive;
}

void IInteractiveElement::OnLookAt()
{
	//TODO	
}

void IInteractiveElement::SetInteractive(bool interactive)
{
	bIsInteractive = interactive;
}

void IInteractiveElement::OnComponentBeginOverlap()
{
	//TODO
}

void IInteractiveElement::OnComponentEndOverlap()
{
	//TODO
}