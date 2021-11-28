// Fill out your copyright notice in the Description page of Project Settings.


#include "HealItemC.h"

#include "GE_UECoddingCharacter.h"
#include "InventorySystemC.h"

void UHealItemC::Use(AGE_UECoddingCharacter* Character)
{
	if(Character)
	{
		Character->InventoryComponent->RemoveItem(this);
		Character->OnPlayerUseHeal.ExecuteIfBound(HealPerSecond,HealRate);
	}
}
