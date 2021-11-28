// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterFollowActorC.generated.h"

class AGE_UECoddingCharacter;

UCLASS()
class GE_UECODDING_API ACharacterFollowActorC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere)
	int32 MaxHealth;
	
	UPROPERTY(BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComp;
	
	UFUNCTION()
	void Damage(int32 DamageAmount);

	UPROPERTY()
	AGE_UECoddingCharacter* Character;

	UFUNCTION()
	void DestroyActor();
	
	ACharacterFollowActorC();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
