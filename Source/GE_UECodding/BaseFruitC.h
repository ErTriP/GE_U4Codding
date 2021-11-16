// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpItem.h"
#include "GameFramework/Actor.h"
#include "BaseFruitC.generated.h"

UCLASS()
class GE_UECODDING_API ABaseFruitC : public AActor
{
	GENERATED_BODY()
	
	
	
public:
	
	UPROPERTY(BlueprintReadWrite)
	class UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	class UInventoryItemC* Item;
	
	// Sets default values for this actor's properties
	ABaseFruitC();
	
	void SpawnConstract(class UInventoryItemC* item_qa);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION( )
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult );

};
