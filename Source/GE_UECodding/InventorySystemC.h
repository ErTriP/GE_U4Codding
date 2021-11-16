// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystemC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GE_UECODDING_API UInventorySystemC : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventorySystemC();

	UFUNCTION()
	bool AddItem(class UInventoryItemC* Item);
	
	UFUNCTION()
	bool RemoveItem(class UInventoryItemC* Item);

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UInventoryItemC*> DefaultItems;

	UPROPERTY(EditDefaultsOnly)
	int32 Capacity;

	UPROPERTY(BlueprintReadOnly)
	TArray<class UInventoryItemC*> ItemsInIncventory;

	UPROPERTY(BlueprintReadOnly)
	TArray<class UPickUpItem*> PickUpActorsInIventory;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdate OnInventoryUpdate;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
		
};
