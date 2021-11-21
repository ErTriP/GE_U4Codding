// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponC.h"

#include "DrawDebugHelpers.h"
#include "GE_UECoddingCharacter.h"

// Sets default values
ABaseWeaponC::ABaseWeaponC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComp);

	MaxAmmo = 42;
	AmmoPerClip = 7;
	Damage = 32;
	ReloadDuration = 1.25f;
	Range = 4000.f;
	MuzzleSocket = FName("MuzzleSocket");
	CurrentAmmo = MaxAmmo - AmmoPerClip;
	CurrentAmmoInClip = AmmoPerClip;
	bIsReloading = false;
	BulletsPerShoot = 1;

}

// Called when the game starts or when spawned
void ABaseWeaponC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeaponC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseWeaponC::CanReload_Implementation()
{
	return  CurrentAmmo > 0 && CurrentAmmoInClip != AmmoPerClip;
}

void ABaseWeaponC::Reload_Implementation()
{
	if (CanReload_Implementation())
	{
		bIsReloading = true;
		
		GEngine->AddOnScreenDebugMessage(-1, ReloadDuration, FColor::Red, FString::Printf(TEXT("Reloading")));
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer,this, &ABaseWeaponC::ResetbIsReload, 0.1f, false, ReloadDuration);
		
		if (CurrentAmmo >= AmmoPerClip - CurrentAmmoInClip)
		{
			CurrentAmmo = CurrentAmmo - (AmmoPerClip - CurrentAmmoInClip);
			CurrentAmmoInClip = AmmoPerClip;
		}else
		{
			CurrentAmmoInClip += CurrentAmmo;
			CurrentAmmo = 0;
		}
		
	}
}

void ABaseWeaponC::WeaponTrace()
{
	UWorld* World = GetWorld();
	if(World)
	{
		struct FHitResult OutHit;
		const FVector& Start = FVector(StaticMeshComp->GetSocketLocation(MuzzleSocket));
		const FVector& End = FVector(StaticMeshComp->GetSocketLocation(MuzzleSocket) + StaticMeshComp->GetForwardVector()*Range);
		World->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
	}
}

void ABaseWeaponC::ResetbIsReload()
{
		GEngine->AddOnScreenDebugMessage(-1, ReloadDuration, FColor::Red, FString::Printf(TEXT("Done")));
		bIsReloading = false;
}

void ABaseWeaponC::Fire()
{
	if (CanFire())
	{
		WeaponTrace();
		UseAmmo();
	}
}

bool ABaseWeaponC::CanFire() const
{
	return CurrentAmmoInClip > 0 && !bIsReloading;
}

void ABaseWeaponC::UseAmmo()
{
	CurrentAmmoInClip -= BulletsPerShoot;
}


