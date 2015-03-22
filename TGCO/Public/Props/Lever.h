
#pragma once

#include "Props/Props.h"
#include "Lever.generated.h"

/**
 * @brief This class define a lever. 
 */
UCLASS()
class TGCO_API ALever : public AProps
{
	GENERATED_BODY()

public:
	/**
	* @brief	Constructor.
	*
	* @param	ObjectInitializer	The object initializer.
	*/
	ALever(const FObjectInitializer& ObjectInitializer);

};
