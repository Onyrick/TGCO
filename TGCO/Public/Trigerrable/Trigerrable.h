#pragma once

#include "Trigerrable.generated.h"

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UTrigerrable :
	public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ITrigerrable{
	GENERATED_IINTERFACE_BODY()
public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Event launch when Player trigger the component.
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Trigerrable", meta = (FriendlyName = "OnComponentBeginOverlap Trigger"))
		virtual void OnComponentBeginOverlap();
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	//Event launch when Player trigger the component.
	//////////////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Trigerrable", meta = (FriendlyName = "OnComponentEndOverlap Trigger"))
		virtual void OnComponentEndOverlap();
	
};