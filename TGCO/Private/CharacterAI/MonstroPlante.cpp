// Fill out your copyright notice in the Description page of Project Settings.

#include "TGCO.h"
#include "TGCOCharacter.h"
#include "EnergyCell.h"
#include "SolutionType.h"
#include "MonstroPlante.h"

AMonstroPlante::AMonstroPlante(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	this->fStunTime = 3.f;
	this->fRespawnTime = 3.f;
	this->fSpeedHit = 2.f;
	this->fPower = 2.f;

	AddNewResistenceSolution(ESolutionType::NONE);
	AddNewResistenceSolution(ESolutionType::NONE);
	AddNewResistenceSolution(ESolutionType::FROZEN_PRODUCT);

	SpawnPoint = NULL;

	GetCharacterMovement()->MaxWalkSpeed = 250.f;

	SolutionSphere1 = PCIP.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("SolutionSphere1"));
	SolutionSphere2 = PCIP.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("SolutionSphere2"));
	SolutionSphere3 = PCIP.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("SolutionSphere3"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere'"));
	ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("MaterialInstanceConstant'/Game/Blueprints/AI/MonstroPlante/Mat_Emissive'"));

	SolutionSphere1->SetStaticMesh(StaticMesh.Object);
	SolutionSphere2->SetStaticMesh(StaticMesh.Object);
	SolutionSphere3->SetStaticMesh(StaticMesh.Object);

	MaterialInstance1 = UMaterialInstanceDynamic::Create(Material.Object, this);
	MaterialInstance2 = UMaterialInstanceDynamic::Create(Material.Object, this);
	MaterialInstance3 = UMaterialInstanceDynamic::Create(Material.Object, this);
	
	SolutionSphere1->SetMaterial(0, MaterialInstance1);
	SolutionSphere2->SetMaterial(0, MaterialInstance2);
	SolutionSphere3->SetMaterial(0, MaterialInstance3);

	SolutionSphere1->RegisterComponentWithWorld(GetWorld());
	SolutionSphere2->RegisterComponentWithWorld(GetWorld());
	SolutionSphere3->RegisterComponentWithWorld(GetWorld());

	SolutionSphere1->AttachTo(RootComponent);
	SolutionSphere2->AttachTo(RootComponent);
	SolutionSphere3->AttachTo(RootComponent);

	AddOwnedComponent(SolutionSphere1);
	AddOwnedComponent(SolutionSphere2);
	AddOwnedComponent(SolutionSphere3);

	
	FVector MonstroPosition = GetActorLocation();

	SolutionSphere1->AddRelativeLocation(FVector(0.f, 40.f, 0.f));
	SolutionSphere2->AddRelativeLocation(FVector(40.f, 0.f, 0.f));
	SolutionSphere3->AddRelativeLocation(FVector(-40.f, 0.f, 0.f));
	
	SolutionSphere1->SetRelativeScale3D(FVector(0.10f, 0.10f, 0.10f));
	SolutionSphere2->SetWorldScale3D(FVector(0.10f, 0.10f, 0.10f));
	SolutionSphere3->SetRelativeScale3D(FVector(0.10f, 0.10f, 0.10f));

	SolutionSphere1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SolutionSphere2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SolutionSphere3->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	SolutionSphere1->SetLockedAxis(ELockedAxis::None);
	SolutionSphere2->SetLockedAxis(ELockedAxis::None);
	SolutionSphere2->SetLockedAxis(ELockedAxis::None);

	SolutionSphere1->SetVisibility(false);
	SolutionSphere2->SetVisibility(false);
	SolutionSphere3->SetVisibility(false);

	m_iIdToReplace = 0;
}

float AMonstroPlante::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	//TODO
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	AProjectile* Projectile = Cast<AProjectile>(DamageCauser);

	if (Projectile == NULL)
		return -1.f;

	if (SolutionResistence.Contains(Projectile->GetSolutionType()) == false && Projectile->GetSolutionType() != ESolutionType::NONE)
	{
		SolutionResistence[m_iIdToReplace] = Projectile->GetSolutionType();
		m_iIdToReplace = (m_iIdToReplace + 1) % 3;

		Destroyed();
		GetWorldTimerManager().SetTimer(this, &AMonstroPlante::RespawnAI, fRespawnTime, false);
		StaticMesh->SetVisibility(false);
	}
	else
	{
		Stun();
	}

	return -1.f;
}

void AMonstroPlante::AddNewResistenceSolution(ESolutionType::Type _solution)
{
	SolutionResistence.Add(_solution);
}

void AMonstroPlante::RemoveResistenceSolution(ESolutionType::Type _solution)
{
	SolutionResistence.Remove(_solution);
}

void AMonstroPlante::Destroyed()
{
	FVector Position = GetActorLocation();
	Super::Destroyed();
	SolutionSphere1->SetVisibility(false);
	SolutionSphere2->SetVisibility(false);
	SolutionSphere3->SetVisibility(false);

	AEnergyCell* energyCell = GetWorld()->SpawnActor<AEnergyCell>(AEnergyCell::StaticClass(), Position, FRotator::ZeroRotator);

}

void AMonstroPlante::RespawnAI()
{
	Super::RespawnAI();
	GetWorld()->GetAuthGameMode()->RestartPlayer(GetAIController());
	if (SpawnPoint != NULL)
	{
		SetActorLocation(SpawnPoint->GetActorLocation());
	}
	
	StaticMesh->SetVisibility(true);
	

	UpdateLights(GetColorOfTheSolution(SolutionResistence[0]), GetColorOfTheSolution(SolutionResistence[1]), GetColorOfTheSolution(SolutionResistence[2]));
}

void AMonstroPlante::UpdateLights_Implementation(FColor _color1, FColor _color2, FColor _color3)
{
	/*MaterialInstance1->SetScalarParameterValue("R", color.X, true, ERHIFeatureLevel::ES2);
	MaterialInstance1->SetScalarParameterValue("G", color.Y, true, ERHIFeatureLevel::ES2);
	MaterialInstance1->SetScalarParameterValue("B", color.Z, true, ERHIFeatureLevel::ES2);

	MaterialInstance2->SetScalarParameterValue("R", color2.X);
	MaterialInstance2->SetScalarParameterValue("G", color2.Y);
	MaterialInstance2->SetScalarParameterValue("B", color2.Z);

	MaterialInstance3->SetScalarParameterValue("R", 1.f);
	MaterialInstance3->SetScalarParameterValue("G", 0.f);
	MaterialInstance3->SetScalarParameterValue("B", 0.f);*/

	SolutionSphere1->SetVisibility(SolutionResistence[0] != ESolutionType::NONE);
	SolutionSphere2->SetVisibility(SolutionResistence[1] != ESolutionType::NONE);
	SolutionSphere3->SetVisibility(SolutionResistence[2] != ESolutionType::NONE);
}

void AMonstroPlante::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	SolutionSphere1->AddLocalOffset(FVector(0.f, -40.f, 0.f));
	SolutionSphere1->AddLocalRotation(FRotator(0.f, 5.f, 0.f));
	SolutionSphere1->AddLocalOffset(FVector(0.f, 40.f, 0.f));

	SolutionSphere2->AddLocalOffset(FVector(-40.f, 0.f, 0.f));
	SolutionSphere2->AddLocalRotation(FRotator(5.f, 5.f, 0.f));
	SolutionSphere2->AddLocalOffset(FVector(40.f, 0.f, 0.f));

	SolutionSphere3->AddLocalOffset(FVector(40.f, 0.f, 0.f));
	SolutionSphere3->AddLocalRotation(FRotator(5.f, -5.f, 0.f));
	SolutionSphere3->AddLocalOffset(FVector(-40.f, 0.f, 0.f));
}

UMaterialInstanceDynamic *AMonstroPlante::GetMaterialInstance(uint32 _num)
{
	switch (_num)
	{
	case 0:
		return MaterialInstance1;
	case 1:
		return MaterialInstance2;
	default:
		return MaterialInstance3;
	}
}