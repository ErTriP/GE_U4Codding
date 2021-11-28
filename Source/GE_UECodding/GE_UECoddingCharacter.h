// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponC.h"
#include "GameFramework/Character.h"
#include "GE_UECoddingCharacter.generated.h"

class ACharacterFollowActorC;

DECLARE_DELEGATE_TwoParams(FOnPlayerUseHeal, int32, int32);
DECLARE_EVENT_OneParam(AGE_UECoddingCharacter, FOnPlayerTakeDamage, int32);
DECLARE_EVENT(AGE_UECoddingCharacter, FOnPlayerDestroy);

UCLASS(config=Game)
class AGE_UECoddingCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	

	
public:
	
	FOnPlayerTakeDamage OnPlayerTakeDamage;
	FOnPlayerDestroy OnPlayerDestroy;
	
	UPROPERTY(BlueprintReadWrite)
	class ACharacterFollowActorC* FollowActor;

	UPROPERTY(BlueprintReadWrite)
	class USpringArmComponent* ArmActorToDestroy;
	
	UPROPERTY(BlueprintReadWrite)
	class ABaseWeaponC* BaseWeapon;
	
	AGE_UECoddingCharacter();
	
	UPROPERTY(EditAnywhere)
	class UInventorySystemC* InventoryComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentHealth;

	UPROPERTY(BlueprintReadWrite)
	int32 MaxHealth;

	UPROPERTY(BlueprintReadWrite)
	int32 Stamina;

	
	UPROPERTY(Transient)
	int32 HealingRate;

	UFUNCTION()
	void DestroyActor();

	UFUNCTION(BlueprintCallable)
	void UseItem(class UInventoryItemC* Item);
	
	UFUNCTION(BlueprintCallable)
	void PickItem(class UInventoryItemC* Item);

	UFUNCTION(BlueprintCallable)
	void DropItem(class UInventoryItemC* Item);

	UFUNCTION()
	void SpawnChildActors();

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION()
	void Reload();

	UFUNCTION()
	void Damage(int32 DamageAmount);

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void Healing(int32 HealPerSecond);

	UFUNCTION()
	void Damaging(int32 DamagePerSecond);

	UFUNCTION()
	void LongHealing(int32 HealPerSecond, int32 Rate);
	
	FTimerHandle HealTimer;
	FTimerDelegate HealTimerDelegate;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	virtual void BeginPlay() override;
	FOnPlayerUseHeal OnPlayerUseHeal;
};




