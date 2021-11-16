// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemC.h"

UInventoryItemC::UInventoryItemC()
{
	DisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

UWorld* UInventoryItemC::GetWorld() const
{
	return World;
}

