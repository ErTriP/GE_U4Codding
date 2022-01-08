#include "PawnWithCamera.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

APawnWithCamera::APawnWithCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	PawnMovementComp = CreateDefaultSubobject<UPawnMovementComponent>(TEXT("PawnMovement"));
	
	StaticMeshComp->SetupAttachment(RootComponent);
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);

	SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3.0f;

	JumpVelocity = 3.f;
	Speed = 2.f;

}


void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

void APawnWithCamera::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.f, 1.f);
}

void APawnWithCamera::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.f, 1.f);
}

void APawnWithCamera::CameraMoveYaw(float AxisValue)
{
	CameraVecInput.Y = FMath::Clamp<float>(AxisValue, -1.f, 1.f);;
}

void APawnWithCamera::TurnMesh(float AxisValue)
{
	TurnMeshValue = FMath::Clamp<float>(AxisValue, -1.f, 1.f);
}

void APawnWithCamera::Jump()
{
	MovementInput.Z = 1;
	GetWorldTimerManager().SetTimer(JumpTimer, this, &APawnWithCamera::StartJump,0.001, false, 1);
}

void APawnWithCamera::StartJump()
{
	MovementInput.Z = -1;
	GetWorldTimerManager().SetTimer(JumpEndTimer, this, &APawnWithCamera::EndJump,0.001, false, 1);
}

void APawnWithCamera::EndJump()
{
	MovementInput.Z = 0;
}

void APawnWithCamera::ZoomIn()
{
	bZooming = true;
}

void APawnWithCamera::ZoomOut()
{
	bZooming = false;
}


void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Zoom in if ZoomIn button is down, zoom back out if it's not
	{
		if (bZooming)
		{
			ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

		//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
		CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		SpringArmComp->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	}

	//Rotate our actor's yaw, which will turn our camera because we're attached to it
	{
		FRotator NewRotation = StaticMeshComp->GetComponentRotation();
		NewRotation.Yaw += TurnMeshValue;
		StaticMeshComp->SetRelativeRotation(NewRotation);
	}

	//Rotate our camera's pitch, but limit it so we're always looking downward
	{
		FRotator NewRotation = StaticMeshComp->GetComponentRotation();
		NewRotation.Pitch = NewRotation.Pitch + CameraVecInput.Y;
		StaticMeshComp->SetWorldRotation(NewRotation);
	}


	//Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!MovementInput.IsZero())
		{
			//Scale our movement input axis values by 100 units per second
			MovementInput = MovementInput.GetSafeNormal() * 100.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += StaticMeshComp->GetForwardVector() * MovementInput.X * DeltaTime * Speed;
			NewLocation += StaticMeshComp->GetRightVector() * MovementInput.Y * DeltaTime * Speed;
			NewLocation +=StaticMeshComp->GetUpVector() * MovementInput.Z * DeltaTime * JumpVelocity;
			SetActorLocation(NewLocation);
		}
	}

}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APawnWithCamera::ZoomOut);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APawnWithCamera::Jump);

	//Hook up every-frame handling for our four axes
	InputComponent->BindAxis("MoveForward", this, &APawnWithCamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APawnWithCamera::MoveRight);
	InputComponent->BindAxis("LookUp", this, &APawnWithCamera::CameraMoveYaw);
	InputComponent->BindAxis("TurnMesh", this, &APawnWithCamera::TurnMesh);


}

