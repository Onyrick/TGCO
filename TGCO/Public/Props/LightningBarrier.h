

#pragma once
#include "Props/Props.h"
#include "Props/LightningBarrierSkeletalMeshComp.h"
#include "LightningBarrier.generated.h"


/**
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
	/** Constructors */
	ALightningBarrier(const FObjectInitializer& PCIP);

	UFUNCTION(BlueprintCallable, Category = "LightningBarrier")
		/**
		 * public  method : Change the active state (whether or not the lightning
		 * is active)
		 * @method:    ChangeActiveState
		 * @return:   void
		 */
		 void ChangeActiveState();

	UFUNCTION()
		void OnRep_LightningState();


	/** Boolean describing the active state of the lightning. Can be edited in
	the unreal editor and have an immediate effect on the instance in the scene */
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_LightningState, EditAnywhere, BlueprintReadOnly, Category = "LightningBarrier")
		bool bIsLightningActive;

	/** Mesh representing the barrier itself */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "LightningBarrier")
		ULightningBarrierSkeletalMeshComp * pBarrier;

	UPROPERTY()
		UStaticMeshComponent * rail1;
	
	UPROPERTY()
		UStaticMeshComponent * rail2;
		

	UPROPERTY(EditAnywhere, Category = "LightningBarrier")
		uint32 ActivateInMotionCheckBox : 1;

	/** Direction of the movement if the barrier is in motion */
	UPROPERTY(Replicated, EditAnywhere, Category = "MovingLightningBarrier")
		EMotionDir eDirection;


	/**  Length of the path the barrier will cover back and forth*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MovingLightningBarrier", meta = (EditCondition = "ActivateInMotionCheckBox"))
		float fLength;

	/** True if the barrier is in motion.  */
	UPROPERTY(Replicated, EditAnywhere, Category = "MovingLightningBarrier", meta = (EditCondition = "ActivateInMotionCheckBox"))
		bool bInMotion;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "MovingLightningBarrier", meta = (EditCondition = "ActivateInMotionCheckBox"))
		URotatingMovementComponent* RotatingMovement;

	UPROPERTY(Replicated, EditAnywhere, Category = "MovingLightningBarrier", meta = (EditCondition = "ActivateInMotionCheckBox"))
		FVector vMotion;

	UPROPERTY(Replicated, EditAnywhere, Category = "MovingLightningBarrier", meta = (EditCondition = "ActivateInMotionCheckBox"))
		FRotator rRotation;

	UPROPERTY()
		UTextRenderComponent *TextRenderComponent;
	
	UPROPERTY()
	UMaterialInstanceDynamic *GhostMaterialInstance;

	UStaticMesh* railshape;

	virtual void ChangeActiveStateFromServer(bool bValue);

	virtual void UpdateActiveState();

	/** delegate used to pickup when the selection has changed */
	void OnActorSelectionChanged(UObject* obj);

#if WITH_EDITOR
	/**
	 * virtual public  method : Method catching property changes event coming from the
	 * unreal editor. This is used to apply the changes during the scene edition to the
	 * modified instance (as opposed to during runtime)
	 * @method:    PostEditChangeProperty
	 * @param: FPropertyChangedEvent & PropertyChangedEvent
	 * @return:   void
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

protected:
	float fPercentageWayCovered;
	bool bCompleted;
};
