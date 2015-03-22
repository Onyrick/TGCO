

#pragma once

#include "Triggerable.h"
#include "MinesweeperBox.generated.h"

/**
*@class	AMinesweeperBox
*
*@brief	Minesweeper box for the minesweeper puzzle
*/
UCLASS()
class TGCO_API AMinesweeperBox : public ATriggerable
{
	GENERATED_BODY()
	
public:
	/**
	*@brief	Constructor.
	*
	*@param	ObjectInitializer	The object initializer.
	 */
	AMinesweeperBox(const FObjectInitializer& ObjectInitializer);

	/**
	*@brief	When walk on a minesweeper box
	*
	*@param OtherActor				If non-null, the other actor.
	*@param OtherComp 				If non-null, the other component.
	*@param	OtherBodyIndex		  	Zero-based index of the other body.
	*@param	bFromSweep			  	true to from sweep.
	*@param	SweepResult			  	The sweep result.
	*
	*### summary	Event launch when Player begin to trigger the TriggerBox component.
	 */
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	/**
	*@brief	Executes the overlap end action.
	*
	*@param OtherActor				If non-null, the other actor.
	*@param OtherComp 				If non-null, the other component.
	*@param	OtherBodyIndex		  	Zero-based index of the other body.
	*
	*### summary	Event launch when Player end to trigger the TriggerBox component.
	 */
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	/**
	*@brief	Sets the variable bIsUndermined, to know if minesweeper box is undermined.
	 */
	void SetIsUndermined();

	/**
	*@brief	Gets is undermined.
	*
	*@return	true if the minesweeper box is undermined, false if it is not.
	 */
	bool GetIsUndermined();

	/**
	*@brief	Sets the variable iNeigbourgsUndermined, the number of neighbours undermined.
	 */
	void SetNeighboursUndermined();

	/**
	*@brief	Gets the number of neighbours undermined.
	*
	*@return	The number of neighbours undermined.
	 */
	unsigned int GetNeighboursUndermined();

	/**
	*@brief	Explodes the mine when the given actor walk on the minesweeper box.
	*		Reinit the Minesweeper Puzzle. Do some damage to the
	*		Player. Eject the Player to the Checkpoint of the Level.
	*
	*@param OtherActor	If non-null, the other actor.
	 */
	void Explode(class AActor* OtherActor);

	/**
	*@brief	Reinitialises the display information.
	*		Set bInfoPast to false.
	 */
	void ReinitDisplayInformation();

	/**
	*@brief	Sets the value to know if there is something to draw on the 
	*		AMinesweeperBox : true -> flag, flase -> no flag.
	*		Can be called in BluePrint
	*/
	UFUNCTION(BlueprintCallable, Category = "MinesweeperBox")
	void SetIsMarked();

	/**
	*@brief	Query if this flag is visible in minesweeper box.
	*		Can be called in BluePrint
	*
	*@return	true if marked, false if not.
	*/
	UFUNCTION(BlueprintCallable, Category = "MinesweeperBox")
	bool IsMarked();

	/**
	*@brief	Sets the visibility of flag.
	*		Can be called in BluePrint
	*/
	UFUNCTION(BlueprintCallable, Category = "MinesweeperBox")
	void SetVisibilityOfFlag();

	/**   
	* @brief	The Text Render representing the number of Neighbours which are undermined.   
	*/
	UPROPERTY(EditAnywhere, Transient, Replicated, BlueprintReadWrite, Category = Text)
	UTextRenderComponent* Number;

	/**   
	*@brief	The Mesh representing a flag. 
	*		It will be visible thanks to the console.
	*/
	UPROPERTY(EditAnywhere, Transient, Replicated, Category = Meshes)
	UStaticMeshComponent* MineFlag;

protected:

	/** @brief	true if this object is undermined. */
	UPROPERTY(Transient, Replicated)
	bool bIsUndermined;

	/** @brief	true if the flag is visible. */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_Flag)
	bool bIsMarked;

	/** @brief	The number of the neighbours undermined. */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_TextRender)
	int32 iNeighboursUndermined;

	/** @brief	true if the number is displayed. */
	bool bIsDisplayed;

	/**
	*@brief	Executes when the number of neighbours undermined, iNeighboursUndermined, changes.
	*		Call by the client.
	*/
	UFUNCTION()
	void OnRep_TextRender();

	/**
	*@brief	Executes when the minesweeper box just being marked, bIsMarked changes.
	*		Call by the client.
	*/
	UFUNCTION()
	void OnRep_Flag();
};
