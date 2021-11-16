// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickUpItem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GE_UECODDING_API UPickUpItem : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UPickUpItem();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInventoryItemC* InventoryItem;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
		
};
