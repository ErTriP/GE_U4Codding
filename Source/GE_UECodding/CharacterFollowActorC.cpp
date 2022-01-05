// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterFollowActorC.h"

#include "GE_UECoddingCharacter.h"



// Sets default values
ACharacterFollowActorC::ACharacterFollowActorC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);

	MaxHealth = 100;
	CurrentHealth = MaxHealth;

}

void ACharacterFollowActorC::Damage(int32 DamageAmount)
{
	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0)
	{
		DestroyActor();		
	}
	
}

// Called when the game starts or when spawned
void ACharacterFollowActorC::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AGE_UECoddingCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	Character->OnPlayerTakeDamage.AddUFunction(this, "Damage");
	Character->OnPlayerDestroy.AddUFunction(this, "DestroyActor");
	
}

void ACharacterFollowActorC::DestroyActor()
{
	Destroy();
}

// Called every frame
void ACharacterFollowActorC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

