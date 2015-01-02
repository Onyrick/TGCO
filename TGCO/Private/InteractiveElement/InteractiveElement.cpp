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
	unimplemented();
}

bool IInteractiveElement::IsInteractive()
{
	//unimplemented();
	return bIsInteractive;
}

void IInteractiveElement::OnLookAt()
{
	unimplemented();
}

void IInteractiveElement::SetInteractive(bool interactive)
{
	//unimplemented();
	bIsInteractive = interactive;
}

void IInteractiveElement::OnComponentBeginOverlap()
{
	unimplemented();
}

void IInteractiveElement::OnComponentEndOverlap()
{
	unimplemented();
}