

#pragma once
#include "Props/Props.h"
#include "Props/LightningBarrierSkeletalMeshComp.h"
#include "Puzzle/BarrierColor.h"
#include "LightningBarrier.generated.h"


/**
 *  @class ALightningBarrier
 *
 * 	@brief Class representing a lightning barrier. The lightning can be switched off
 *	Enum listing all movement direction
 * - None means the barrier is static
 * - X, Y, Z are translation along the corresponding axis
 * - RY, RZ are rotation on the corresponding axis
 */
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EMotionDir : uint8
{
	VE_None 	UMETA(DisplayName = "None"),
	VE_X_Axis 	UMETA(DisplayName = "X_Axis"),
	VE_Y_Axis 	UMETA(DisplayName = "Y_Axis"),
	VE_Z_Axis	UMETA(DisplayName = "Z_Axis"),
	VE_RY_Axis	UMETA(DisplayName = "RY_Axis"),
	VE_RZ_Axis	UMETA(DisplayName = "RZ_Axis")
};

/**
 * Class representing a lightning barrier. The lightning can be switched off
 * by the use of a @ref ALightningSwitch instance
 */

UCLASS()
class TGCO_API ALightningBarrier : public AProps
{
	GENERATED_BODY()

public:
	/** @brief Constructor */
	ALightningBarrier(const FObjectInitializer& ObjectInitializer);

	/**
	* @brief Toggle the active state (whether or not the lightning
	* is active)
	*
	* @return void
	*/
	UFUNCTION(BlueprintCallable, Category = "LightningBarrier")
		void ChangeActiveState();

	/**
	* @brief Force the active state to a given one.

	* @param bool the new state
	* @return void
	*/
	UFUNCTION(BlueprintCallable, Category = "LightningBarrier")
		void SetActiveState(bool state);

	/**
	* @brief Function automatically called when @ref bIsLightningActive is replicated
	*
	* @return void
	*/
	UFUNCTION()
		void OnRep_LightningState();


	/**
	* @brief Function called at launch game
	*
	* @return void
	*/
	UFUNCTION()
		void BeginPlay();

	/**
	* @brief Change the active state of the barrier (on the client side) using the value sent by the server
	* 
	* @param bool the new barrier' state 
	* @return void
	*/
	virtual void ChangeActiveStateFromServer(bool bValue);

	/**
	* @brief Apply the LightningBarrier state to its @ref ULightningBarrierSkeletalMeshComp pBarrier
	* so that it visually changes in the scene (displays or hides the ligthning between the 2 poles of the 
	* barrier depending on its current state)
	*
	* @return void
	*/
	virtual void UpdateActiveState();

public:
	/** Boolean describing the active state of the lightning. Can be edited in
	the unreal editor and have an immediate effect on the instance in the scene */
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_LightningState, EditAnywhere, BlueprintReadOnly, Category = "LightningBarrier")
		bool bIsLightningActive;

	/** Mesh representing the barrier itself */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "LightningBarrier")
		ULightningBarrierSkeletalMeshComp * pBarrier;

	/** Mesh representing the barrier itself */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "LightningBarrier")
		ALightningBarrier * pFutureBarrier;

	/** Color of the barrier. Used to have a visual aid to know which switches control the barrier*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "LightningBarrier")
		EBarrierColor eBarColor;

	/** First rail mesh on which the barrier will be translating in case of a moving barrier*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "LightningBarrier")
		UStaticMeshComponent * rail1;

	/** Second rail mesh on which the barrier will be translating in case of a moving barrier*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "LightningBarrier")
		UStaticMeshComponent * rail2;

	/** Boolean used to specify whether or not the barrier is a moving one*/
	UPROPERTY(EditAnywhere, Category = "LightningBarrier")
		uint32 ActivateInMotionCheckBox : 1;

	/** Direction of the movement if the barrier is in motion */
	UPROPERTY(Replicated, EditAnywhere, Category = "LightningBarrier")
		EMotionDir eDirection;

	/**  Length of the path the barrier will cover back and forth*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MovingLightningBarrier", meta = (EditCondition = "ActivateInMotionCheckBox"))
		float fLength;

	/** True if the barrier is in motion.  */
	UPROPERTY(Replicated, EditAnywhere, Category = "MovingLightningBarrier", meta = (EditCondition = "ActivateInMotionCheckBox"))
		bool bInMotion;
	
	/** Rotation of barrier in case of a rotating barrier*/ 
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MovingLightningBarrier", meta = (EditCondition = "ActivateInMotionCheckBox"))
		URotatingMovementComponent* RotatingMovement;
	
	/** Vector used to control the motion of a moving barrier*/
	UPROPERTY(Replicated, EditAnywhere, Category = "MovingLightningBarrier", meta = (EditCondition = "ActivateInMotionCheckBox"))
		FVector vMotion;

	/** Rotator used to control the motion of a rotating barrier*/
	UPROPERTY(Replicated, EditAnywhere, Category = "MovingLightningBarrier", meta = (EditCondition = "ActivateInMotionCheckBox"))
		FRotator rRotation;

	/** Shape of the rails on which a translating barrier will slide*/ 
	UStaticMesh* railshape;


	/** delegate used to pickup when the selection has changed */
	void OnActorSelectionChanged(UObject* obj);

	/**
	 * @brief Method catching property changes event coming from the
	 * unreal editor. This is used to apply the changes during the scene edition to the
	 * modified instance (as opposed to during runtime)
	 *
	 * @param FPropertyChangedEvent & PropertyChangedEvent
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

};
