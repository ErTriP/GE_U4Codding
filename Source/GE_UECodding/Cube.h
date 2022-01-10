// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cube.generated.h"


UENUM(BlueprintType)
enum class EStatus : uint8
{
	Active,
	Deactive,
	MAX
};

UCLASS()

class GE_UECODDING_API ACube : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	EStatus Status;

	FTimerHandle TH;


public:
	// Sets default values for this actor's properties
	ACube();

	UPROPERTY(EditAnywhere)
	UMaterialInstance* ActiveMat;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* DeactiveMat;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ChangeStatus();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
