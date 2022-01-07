// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnWithCamera.generated.h"

UCLASS()
class GE_UECODDING_API APawnWithCamera : public APawn
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComp;



public:
	UPROPERTY(EditAnywhere)
	UPawnMovementComponent* PawnMovementComp;
	
	APawnWithCamera();
	
	FVector MovementInput;
	FVector2D CameraVecInput;
	bool bIsJumping;
	bool bZooming;
	float TurnMeshValue;

	FTimerHandle JumpTimer;
	FTimerHandle JumpEndTimer;
	
	UPROPERTY(EditAnywhere)
	float ZoomFactor;
	
	UPROPERTY(EditAnywhere)
	float JumpVelocity;
	
	UPROPERTY(EditAnywhere)
	float Speed;

protected:
	virtual void BeginPlay() override;

public:	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void CameraMoveYaw(float AxisValue);
	void TurnMesh(float AxisValue);
	void Jump();
	void StartJump();
	void EndJump();
	void ZoomIn();
	void ZoomOut();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
