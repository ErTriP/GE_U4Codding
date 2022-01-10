// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"


// Sets default values
ACube::ACube()
{
	
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	Status = EStatus::Active;
	
	GetWorldTimerManager().SetTimer(TH, this, &ACube::ChangeStatus, 2.f, true, 2.f);
}

void ACube::ChangeStatus()
{
	if (Status == EStatus::Active)
	{
		StaticMeshComp->SetMaterial(0, DeactiveMat);
		Status = EStatus::Deactive;
	}else
	{
		StaticMeshComp->SetMaterial(0, ActiveMat);
		Status = EStatus::Active;
	}
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

