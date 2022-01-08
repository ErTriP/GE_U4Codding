
#include "BasePawnPZ7.h"

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
}

