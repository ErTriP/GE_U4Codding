// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageItemC.h"

#include "GE_UECoddingCharacter.h"
#include "InventorySystemC.h"

void UDamageItemC::Use(AGE_UECoddingCharacter* Character)
{
	if(Character)
	{
		Character->InventoryComponent->RemoveItem(this);
		Character->OnPlayerUseHeal.ExecuteIfBound(DamagePerSecond*-1,DamageRate);
	}
}

