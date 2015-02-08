

#pragma once

#include "GameFramework/Actor.h"
#include "MinesBox.generated.h"

/**
 * 
 */
UCLASS()
class TGCO_API AMinesBox : public AActor
{
	GENERATED_BODY()
	
public:
	/** Constructors */
	AMinesBox(const FObjectInitializer& PCIP);

	/** Getter and Setter of the variable bIsUndermined */
	void SetIsUndermined();
	bool GetIsUndermined();

	/** Getter and Setter of the variable iNeigbourgsUndermined */
	void SetNeighboursUndermined();
	unsigned int GetNeighboursUndermined();

	UPROPERTY(EditAnywhere, Category = "Static Meshes")
		UStaticMeshComponent* StaticMesh;
	
protected:
	/** The position of the mine box */

	/** Wheteher a mineBox is undermined */
	bool bIsUndermined;

	/** The number of neighbourgs which are undermined */
	unsigned int iNeighboursUndermined;
	
};
