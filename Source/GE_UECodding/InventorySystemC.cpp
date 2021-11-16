// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystemC.h"

#include "InventoryItemC.h"

// Sets default values for this component's properties
UInventorySystemC::UInventorySystemC()
{
	Capacity = 20;
}

bool UInventorySystemC::AddItem(UInventoryItemC* Item)
{

	if (ItemsInIncventory.Num() >= Capacity || !Item)
	{
		return false;
	}

	Item->Inventory = this;
	Item->World = GetWorld();
	ItemsInIncventory.Add(Item);


	//UpdateUI
	OnInventoryUpdate.Broadcast();

	return true;
	
}

bool UInventorySystemC::RemoveItem(UInventoryItemC* Item)
{
	if(Item)
	{
		Item->Inventory = nullptr;
		Item->World = nullptr;
		ItemsInIncventory.RemoveSingle(Item);
		OnInventoryUpdate.Broadcast();
		return true;
	}
	return false;
}


// Called when the game starts
void UInventorySystemC::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
	
}




