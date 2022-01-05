// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemC.h"
#include "DamageItemC.generated.h"

/**
 * 
 */
UCLASS()
class GE_UECODDING_API UDamageItemC : public UInventoryItemC
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	int32 DamagePerSecond;

	UPROPERTY(EditDefaultsOnly)
	int32 DamageRate;

	virtual void Use(AGE_UECoddingCharacter* Character) override;
};
