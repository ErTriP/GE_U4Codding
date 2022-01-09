#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "BasePawnPZ7.generated.h"

DECLARE_DELEGATE_OneParam(FOnCubeSpawned, TArray<AActor*> &)

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

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> SpawnedActors;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AActor> BPCube;
	
protected:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void SpawnActor();
	void RemoveSpawnedActors();
	
	virtual void BeginPlay() override;

	UPROPERTY()
	APlayerController* PC;

	FTimerHandle TH;

public:
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
