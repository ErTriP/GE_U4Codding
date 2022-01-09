
#include "BasePawnPZ7.h"
#include "Chaos/AABB.h"
#include "GameFramework/FloatingPawnMovement.h"

ABasePawnPZ7::ABasePawnPZ7()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SetRootComponent(SphereComp);
	StaticMeshComp->SetupAttachment(RootComponent);
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	
	MovementComp = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComp->SetUpdatedComponent(SphereComp);

	SphereComp->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	SphereComp->SetSphereRadius(50.f);

	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 30.0f), FRotator(-30.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
}

void ABasePawnPZ7::SpawnActor()
{
	int32 Num = FMath::RandRange(1, 100);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Num %d"), Num));
	FVector Pos = GetActorLocation();
	FRotator Rot = GetActorRotation();
	FActorSpawnParameters Parameters;
	
	for (int i = 1; i < Num + 1; i++)
	{
		Pos += GetActorForwardVector() * 150 * i;
		SpawnedActors.Add(GetWorld()->SpawnActor(BPCube.Get(), &Pos, &Rot, Parameters));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Pos.ToString());
	}

	GetWorldTimerManager().SetTimer(TH, this, &ABasePawnPZ7::RemoveSpawnedActors, 0.0001, false, 5.f);
}

void ABasePawnPZ7::RemoveSpawnedActors()
{
	for (auto SpawnedActor: SpawnedActors)
	{
		SpawnedActor->Destroy();
	}
	SpawnedActors.Empty();
}

void ABasePawnPZ7::MoveForward(float AxisValue)
{
	if (AxisValue != 0)
	{
		AddMovementInput(PC->GetViewTarget()->FindComponentByClass<UCameraComponent>()->GetForwardVector() * AxisValue);
	}
}

void ABasePawnPZ7::MoveRight(float AxisValue)
{
	if (AxisValue != 0)
	{
		AddMovementInput(PC->GetViewTarget()->FindComponentByClass<UCameraComponent>()->GetRightVector() * AxisValue);
	}
}

void ABasePawnPZ7::BeginPlay()
{
	Super::BeginPlay();
	PC = GetWorld()->GetFirstPlayerController();
	
}


void ABasePawnPZ7::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawnPZ7::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePawnPZ7::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePawnPZ7::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasePawnPZ7::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ABasePawnPZ7::AddControllerYawInput);
	PlayerInputComponent->BindAction("SpawnActor", IE_Pressed, this, &ABasePawnPZ7::SpawnActor);
}

