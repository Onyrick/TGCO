
#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveElement.h"
#include "ConsoleTuto.generated.h"

/**
 * @brief First test for interactive element
 * 	
 * 	@sa AInteractiveElement
 */
UCLASS()
class TGCO_API AConsoleTuto : public AInteractiveElement
{
	GENERATED_BODY()

public:
	/** @brief Constructor */
	AConsoleTuto(const FObjectInitializer& ObjectInitializer);

	/** @brief Called when the Player uses the object */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	virtual bool OnInteract() override;
	
	/** @brief Getter for bIsUnlocked */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	bool IsUnlocked();

	/** @brief Setter for bIsUnlocked */
	UFUNCTION(BlueprintCallable, Category = "InteractiveElement")
	void SetUnlocked(bool _unlock);

protected:
	/** @brief Whether the console is unlocked */
	bool bIsUnlocked;
};
