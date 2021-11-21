// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RealoadableInterface.h"
#include "GameFramework/Actor.h"
#include "BaseWeaponC.generated.h"

UCLASS()
class GE_UECODDING_API ABaseWeaponC : public AActor, public IRealoadableInterface
{
	GENERATED_BODY()

	FTimerHandle ReloadTimer;
	
public:	
	UPROPERTY(BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComp;
	
	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly)
	int32 AmmoPerClip;

	UPROPERTY(EditDefaultsOnly)
	int32 Damage;

	UPROPERTY(EditDefaultsOnly)
	float ReloadDuration;

	UPROPERTY(EditDefaultsOnly)
	float Range;

	UPROPERTY(EditDefaultsOnly)
	FName MuzzleSocket;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 CurrentAmmo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 CurrentAmmoInClip;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsReloading;

	UPROPERTY(EditDefaultsOnly)  
	int32 BulletsPerShoot;
	
	ABaseWeaponC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual bool CanReload_Implementation() override;
	
	virtual void Reload_Implementation() override;
	
	UFUNCTION()
	void WeaponTrace();

	UFUNCTION()
	void ResetbIsReload();
	
	UFUNCTION()
	void Fire();
	
	UFUNCTION()
	bool CanFire() const;
	
	UFUNCTION()
	void UseAmmo();
};
