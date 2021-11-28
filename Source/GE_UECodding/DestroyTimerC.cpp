// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyTimerC.h"

// Sets default values for this component's properties
UDestroyTimerC::UDestroyTimerC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UDestroyTimerC::DestroyActor()
{
	if(GetOwner())
	{
		GetOwner()->Destroy();
	}
}

// Called when the game starts
void UDestroyTimerC::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &UDestroyTimerC::DestroyActor, 0.1f, false, TimeToDestroy);

	// ...
	
}


// Called every frame
void UDestroyTimerC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

