#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "BasePawnPZ7.generated.h"

UCLASS()
class GE_UECODDING_API ABasePawnPZ7 : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UPawnMovementComponent* MovementComp;

public:
	
	ABasePawnPZ7();

protected:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	
	virtual void BeginPlay() override;

	UPROPERTY()
	APlayerController* PC;

public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
