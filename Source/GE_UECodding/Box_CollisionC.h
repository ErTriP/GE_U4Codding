// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Box_CollisionC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorBeginOverlapC);
DECLARE_DYNAMIC_DELEGATE(FOnActorBeginOverlapDynamic);

UCLASS()
class GE_UECODDING_API ABox_CollisionC : public AActor
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp;
	
	FComponentBeginOverlapSignature ComponentBeginOverlapSignature;
	
	UPROPERTY(BlueprintAssignable)
	FOnActorBeginOverlapC OnActorBeginOverlapC;
	
	FOnActorBeginOverlapDynamic OnActorBeginOverlapDynamic;
	
	ABox_CollisionC();

protected:
	UFUNCTION()
	void MoveActor();

	UFUNCTION( )
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult );
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
