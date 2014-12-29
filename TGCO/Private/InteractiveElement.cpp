#include "TGCO.h"
#include "InteractiveElement.h"

UInteractiveElement::UInteractiveElement(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP)
{

}

void IInteractiveElement::SetInteractive(bool _interactive)
{
	bIsInteractive = _interactive;
}

bool IInteractiveElement::IsInteractive()
{
	return bIsInteractive;
}