// Fill out your copyright notice in the Description page of Project Settings.


#include "Box_CollisionC.h"

#include "GE_UECoddingCharacter.h"

// Sets default values
ABox_CollisionC::ABox_CollisionC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetBoxExtent(FVector(128,128,128));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABox_CollisionC::BeginOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);
	
	OnActorBeginOverlapDynamic.BindUFunction(this, "MoveActor");
	OnActorBeginOverlapC.Add(OnActorBeginOverlapDynamic);
	
}

void ABox_CollisionC::MoveActor()
{
	SetActorLocation(GetActorLocation()+FVector(100, 0 ,0));
}

void ABox_CollisionC::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGE_UECoddingCharacter* Character = Cast<AGE_UECoddingCharacter>(OtherActor);
	if(Character)
	{
		OnActorBeginOverlapC.Broadcast();
	}
}

// Called when the game starts or when spawned
void ABox_CollisionC::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ABox_CollisionC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



