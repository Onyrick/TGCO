
#include "TGCO.h"
#include "TGCOCharacter.h"
#include "SolutionType.h"
#include "MonstroPlante.h"

AMonstroPlante::AMonstroPlante(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), InitializedMaterials(false)
{
	this->fStunTime = 3.f;
	this->fRespawnTime = 3.f;
	this->fSpeedHit = 2.f;
	this->fPower = 50.f;
	this->m_bNeedToAvoid = false;
	this->fSpeedDefault = 400.f;
	this->fSpeedUp = 300.f;

	SolutionResistence.Add(ESolutionType::NONE);
	SolutionResistence.Add(ESolutionType::NONE);
	SolutionResistence.Add(ESolutionType::NONE);
	SolutionResistence.Add(ESolutionType::NONE);

	SpawnPoint = nullptr;

	GetCharacterMovement()->MaxWalkSpeed = fSpeedDefault;

	SolutionSphere1 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("SolutionSphere1"));
	SolutionSphere2 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("SolutionSphere2"));
	SolutionSphere3 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("SolutionSphere3"));
	SolutionSphere4 = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("SolutionSphere4"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshSphere(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere'"));

	SolutionSphere1->SetStaticMesh(StaticMeshSphere.Object);
	SolutionSphere2->SetStaticMesh(StaticMeshSphere.Object);
	SolutionSphere3->SetStaticMesh(StaticMeshSphere.Object);
	SolutionSphere4->SetStaticMesh(StaticMeshSphere.Object);

	SolutionSphere1->RegisterComponentWithWorld(GetWorld());
	SolutionSphere2->RegisterComponentWithWorld(GetWorld());
	SolutionSphere3->RegisterComponentWithWorld(GetWorld());
	SolutionSphere4->RegisterComponentWithWorld(GetWorld());

	SolutionSphere1->AttachTo(RootComponent);
	SolutionSphere2->AttachTo(RootComponent);
	SolutionSphere3->AttachTo(RootComponent);
	SolutionSphere4->AttachTo(RootComponent);


	AddOwnedComponent(SolutionSphere1);
	AddOwnedComponent(SolutionSphere2);
	AddOwnedComponent(SolutionSphere3);
	AddOwnedComponent(SolutionSphere4);


	SolutionSphere1->AddRelativeLocation(FVector(0.f, 40.f, 0.f));
	SolutionSphere2->AddRelativeLocation(FVector(40.f, 0.f, 0.f));
	SolutionSphere3->AddRelativeLocation(FVector(-40.f, 0.f, 0.f));
	SolutionSphere4->AddRelativeLocation(FVector(40.f, 0.f, 0.f));
	
	SolutionSphere1->SetRelativeScale3D(FVector(0.10f, 0.10f, 0.10f));
	SolutionSphere2->SetRelativeScale3D(FVector(0.10f, 0.10f, 0.10f));
	SolutionSphere3->SetRelativeScale3D(FVector(0.10f, 0.10f, 0.10f));
	SolutionSphere4->SetRelativeScale3D(FVector(0.10f, 0.10f, 0.10f));

	SolutionSphere1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SolutionSphere2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SolutionSphere3->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SolutionSphere4->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	SolutionSphere1->SetVisibility(false);
	SolutionSphere2->SetVisibility(false);
	SolutionSphere3->SetVisibility(false);
	SolutionSphere4->SetVisibility(false);

	TriggerBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxTrigger_InteractiveElement"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMonstroPlante::OnOverlapBegin);

	TriggerBox->AttachTo(RootComponent);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	MaterialArray = TArray<UMaterialInstanceDynamic*>();

	SpeedDefault();

}

void AMonstroPlante::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInterface* MeshMat = SolutionSphere1->GetMaterial(0);
	MaterialArray.Push(UMaterialInstanceDynamic::Create(MeshMat, this));
	MeshMat = SolutionSphere2->GetMaterial(0);
	MaterialArray.Push(UMaterialInstanceDynamic::Create(MeshMat, this));
	MeshMat = SolutionSphere3->GetMaterial(0);
	MaterialArray.Push(UMaterialInstanceDynamic::Create(MeshMat, this));
	MeshMat = SolutionSphere4->GetMaterial(0);
	MaterialArray.Push(UMaterialInstanceDynamic::Create(MeshMat, this));

	UpdateLights();
}

float AMonstroPlante::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	AProjectile* Projectile = Cast<AProjectile>(DamageCauser);

	if (Projectile == nullptr)
		return -1.f;

	if (SolutionResistence.Contains(Projectile->GetSolutionType()) == false && Projectile->GetSolutionType() != ESolutionType::NONE)
	{
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

void AMonstroPlante::Destroyed()
{
	if (Role < ROLE_Authority)
	{
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerDestroyMonster(this);
		}
	}
	else
	{
		Super::Destroyed();
		SolutionSphere1->SetVisibility(false);
		SolutionSphere2->SetVisibility(false);
		SolutionSphere3->SetVisibility(false);
		SolutionSphere4->SetVisibility(false);
	}
}

void AMonstroPlante::RespawnAI()
{
	Super::RespawnAI();

	if (GetAIController() != NULL)
	{
		GetWorld()->GetAuthGameMode()->RestartPlayer(GetAIController());
	}
	
	if (SpawnPoint != nullptr)
	{
		SetActorLocation(SpawnPoint->GetActorLocation());
	}
	
	StaticMesh->SetVisibility(true);

	m_bNeedToAvoid = false;

	SpeedDefault();

	UpdateLights();
}

void AMonstroPlante::UpdateLights()
{
	SolutionSphere1->SetVisibility(SolutionResistence[0] != ESolutionType::NONE);
	SolutionSphere2->SetVisibility(SolutionResistence[1] != ESolutionType::NONE);
	SolutionSphere3->SetVisibility(SolutionResistence[2] != ESolutionType::NONE);
	SolutionSphere4->SetVisibility(SolutionResistence[3] != ESolutionType::NONE);

	for (int i = 0; i < MaterialArray.Num(); ++i)
	{
		if (SolutionResistence[i] == ESolutionType::NONE)
			continue;

		MaterialArray[i]->SetVectorParameterValue(FName(TEXT("Color")), GetColorOfTheSolution(SolutionResistence[i]));
		MaterialArray[i]->SetScalarParameterValue(FName(TEXT("Intensity")), 3);
		SolutionSphere1->SetMaterial(0, MaterialArray[i]);
	}
	SolutionSphere1->SetMaterial(0, MaterialArray[0]);
	SolutionSphere2->SetMaterial(0, MaterialArray[1]);
	SolutionSphere3->SetMaterial(0, MaterialArray[2]);
	SolutionSphere4->SetMaterial(0, MaterialArray[3]);
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

	SolutionSphere4->AddLocalOffset(FVector(-40.f, 0.f, 0.f));
	SolutionSphere4->AddLocalRotation(FRotator(5.f, 5.f, 0.f));
	SolutionSphere4->AddLocalOffset(FVector(40.f, 0.f, 0.f));
}

void AMonstroPlante::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AProjectile *projectile = Cast<AProjectile>(OtherActor);

	if (projectile != nullptr)
	{
		SetNeedToAvoid(true);
	}
}

void AMonstroPlante::SetNeedToAvoid(bool _avoid)
{	
	if (Role < ROLE_Authority)
	{
		ATGCOPlayerController * PC;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			PC = Cast<ATGCOPlayerController>(Iterator->Get());
			PC->ServerSetNeedToAvoidMonster(this, _avoid);
		}
	}
	else
	{
		m_bNeedToAvoid = _avoid;
	}
}

void AMonstroPlante::UnStun()
{
	Super::UnStun();
}

void AMonstroPlante::SpeedUp()
{
	GetCharacterMovement()->MaxWalkSpeed = fSpeedDefault + fSpeedUp;
}

void AMonstroPlante::SpeedDefault()
{
	GetCharacterMovement()->MaxWalkSpeed = fSpeedDefault;
}

void AMonstroPlante::SpeedDefaultUp()
{
	fSpeedDefault += 50.f;
	SpeedDefault();
}

void AMonstroPlante::SetSolutionArray(const TArray<ESolutionType::Type> &_solutions)
{
	if (_solutions.Num() > 4) return;
	
	for (int i = 0; i < _solutions.Num(); ++i)
	{
		SolutionResistence[i] = _solutions[i];
	}
	for (int i = _solutions.Num(); i < 4; ++i)
	{
		SolutionResistence[i] = ESolutionType::NONE;
	}

	UpdateLights();
}

void AMonstroPlante::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Replicate to everyone
	DOREPLIFETIME(AMonstroPlante, m_bNeedToAvoid);
}