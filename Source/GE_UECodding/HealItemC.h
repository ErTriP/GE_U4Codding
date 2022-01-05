// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemC.h"
#include "HealItemC.generated.h"

/**
 * 
 */
UCLASS()
class GE_UECODDING_API UHealItemC : public UInventoryItemC
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 HealPerSecond;

	UPROPERTY(EditDefaultsOnly)
	int32 HealRate;

	virtual void Use(AGE_UECoddingCharacter* Character) override;
	
};
