
#pragma once

#include "Monster.h"
#include "SolutionType.h"
#include "BotTargetPoint.h"
#include "EnergyCell.h"
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

	/**********************************************************************************************//**
	 * @brief	Adds a new resistence solution to the array.
	 *
	 * @param	_solution	The solution to add.
	 **************************************************************************************************/

	void AddNewResistenceSolution(ESolutionType::Type _solution);

	/**********************************************************************************************//**
	 * @brief	Removes the resistence solution described by _solution.
	 *
	 * @param	_solution	The solution to remove.
	 **************************************************************************************************/

	void RemoveResistenceSolution(ESolutionType::Type _solution);

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

	/** @brief	wether the monstroplante has to avoid. */
	bool m_bNeedToAvoid;

protected:	
	/** @brief	The solution resistence array. */
	TArray<ESolutionType::Type> SolutionResistence;

	/** @brief	The first sphere material instance. */
	UMaterialInstanceDynamic *MaterialInstance1;
	/** @brief	The second sphere material instance. */
	UMaterialInstanceDynamic *MaterialInstance2;
	/** @brief	The third sphere material instance. */
	UMaterialInstanceDynamic *MaterialInstance3;

	/**********************************************************************************************//**
	 * @brief	The function called every Tick.
	 *
	 * @param	DeltaSeconds	The delta in seconds.
	 **************************************************************************************************/

	virtual void Tick(float DeltaSeconds) override;

	/** @brief	The current id in the solution array. */
	int m_iIdToReplace;

	/** @brief	wether the materials are initialized. */
	bool InitializedMaterials;
};
