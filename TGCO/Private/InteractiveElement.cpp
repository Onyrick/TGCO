#include "TGCO.h"
#include "InteractiveElement.h"

UInteractiveElement::UInteractiveElement(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP)
{

}

void IInteractiveElement::OnInteract_Implementation()
{
	unimplemented();
}

void IInteractiveElement::Highlight_Implementation(bool highlight)
{
	unimplemented();
}

bool IInteractiveElement::IsInteractive_Implementation()
{
	unimplemented();
	return false;
}

void IInteractiveElement::OnLookAt_Implementation()
{
	unimplemented();
}

void IInteractiveElement::SetInteractive_Implementation(bool interactive)
{
	unimplemented();
}

void IInteractiveElement::OnComponentBeginOverlap_Implementation()
{
	unimplemented();
}

void IInteractiveElement::OnComponentEndOverlap_Implementation()
{
	unimplemented();
}