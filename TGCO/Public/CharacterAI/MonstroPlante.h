
#pragma once

#include "Monster.h"
#include "SolutionType.h"
#include "BotTargetPoint.h"
#include "MonstroPlante.generated.h"


/**********************************************************************************************//**
 * @brief	A specific type of monster, the MonstroPlante.
 **************************************************************************************************/

UCLASS()
class TGCO_API AMonstroPlante : public AMonster
{
	GENERATED_UCLASS_BODY()

public:
	/**********************************************************************************************//**
	* @brief	Take damage.
	*
	* @param	DamageAmount		   	The damage amount.
	* @param	DamageEvent			   	The damage event.
	* @param 	EventInstigator	        If non-null, the event instigator.
	* @param 	DamageCauser   	        If non-null, the damage causer.
	*
	* @return	The damage actually applied.
	*
	* ### summary	Event launch when the MonstroPlante take damage.
	**************************************************************************************************/
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;


	/** @brief	Event launched when the monster has to be destroyed. */
	virtual void Destroyed();

	/** @brief	Respawn this MonstroPlante. */
	void RespawnAI();

	/** @brief	The spawn point where the monstroplante will respawn. */
	UPROPERTY(EditAnywhere, Category = "SpawnPoint")
	ABotTargetPoint* SpawnPoint;

	/** @brief	How fast the monstroplante will wait before hitting again. */
	UPROPERTY(EditAnywhere, Category = "Characteristics")
	float fSpeedHit;

	/** @brief	The amount of damage caused by a hit. */
	UPROPERTY(EditAnywhere, Category = "Characteristics")
	float fPower;

	/** @brief	A static mesh component representing one solution resistence*. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class UStaticMeshComponent* SolutionSphere1;

	/** @brief	A static mesh component representing one solution resistence*. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class UStaticMeshComponent* SolutionSphere2;

	/** @brief	A static mesh component representing one solution resistence*. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class UStaticMeshComponent* SolutionSphere3;

	/** @brief	A static mesh component representing one solution resistence*. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class UStaticMeshComponent* SolutionSphere4;

	/** @brief	The trigger box to activate the avoiding processus. */
	UPROPERTY(EditAnywhere, Category = "Triggers")
	UBoxComponent* TriggerBox;

	/**********************************************************************************************//**
	 * @brief	When a projectile enter the box, the monster will try to avoid it.
	 *
	 * @param 	OtherActor	        If non-null, the other actor.
	 * @param   OtherComp 	        If non-null, the other component.
	 * @param	OtherBodyIndex	  	Zero-based index of the other body.
	 * @param	bFromSweep		  	true to from sweep.
	 * @param	SweepResult		  	The sweep result.
	 **************************************************************************************************/
	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/** @brief	Unstun the monstroplante. */
	virtual void UnStun() override;

	/** @brief	Updates the lights color of the spheres. */
	void UpdateLights();

	/** @brief	Increase the walkspeed. */
	void SpeedUp();

	/** @brief	Set the walkspeed to default. */
	void SpeedDefault();

	/** @brief	Speed default up. */
	void SpeedDefaultUp();

	/**********************************************************************************************//**
	 * @brief	Sets need to avoid.
	 *
	 * @param	_avoid	true to avoid.
	 **************************************************************************************************/

	void SetNeedToAvoid(bool _avoid);

	/**********************************************************************************************//**
	 * @brief	Set array by _solution.
	 *
	 * @param	_solution	The solutions.
	 **************************************************************************************************/

	void SetSolutionArray(const TArray<ESolutionType::Type> &_solutions);

	/**
	* @brief	On begin play, create the mastermind.
	*/
	virtual void BeginPlay() override;

	/** @brief	wether the monstroplante has to avoid. */
	UPROPERTY(Transient, Replicated)
	bool m_bNeedToAvoid;

protected:	
	/** @brief	The solution resistence array. */
	TArray<ESolutionType::Type> SolutionResistence;

	/**********************************************************************************************//**
	 * @brief	The function called every Tick.
	 *
	 * @param	DeltaSeconds	The delta in seconds.
	 **************************************************************************************************/

	virtual void Tick(float DeltaSeconds) override;

	/** @brief	wether the materials are initialized. */
	bool InitializedMaterials;

	float fSpeedDefault;
	float fSpeedUp;

	/** Array of materials for diodes*/
	TArray<UMaterialInstanceDynamic*> MaterialArray;
};
