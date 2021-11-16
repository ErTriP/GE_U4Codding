// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFruitC.h"

#include "GE_UECoddingCharacter.h"
#include "InventoryItemC.h"
#include "Components/BoxComponent.h"

// Sets default values
void ABaseFruitC::SpawnConstract(UInventoryItemC* item_qa)
{
	Item = item_qa;
}

ABaseFruitC::ABaseFruitC()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	BoxCollision->SetBoxExtent(FVector(128,128,128));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseFruitC::BeginOverlap);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseFruitC::BeginPlay()
{
	Super::BeginPlay();
	if(Item->PickUpMesh)
	{	
		StaticMesh->SetStaticMesh(Item->PickUpMesh);
	}
	
}

// Called every frame
void ABaseFruitC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseFruitC::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGE_UECoddingCharacter* Character = Cast<AGE_UECoddingCharacter>(OtherActor);
	if(Character)
	{
		Character->PickItem(Item);
		Destroy();
	}
}

