// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItemC.generated.h"


UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class GE_UECODDING_API UInventoryItemC : public UObject
{
	GENERATED_BODY()
	
public:

	UInventoryItemC();

	virtual class UWorld* GetWorld() const override;
	
	UPROPERTY(Transient)
	class UWorld* World;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText UseActionText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class  UStaticMesh* PickUpMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTexture2D* Thumbnail;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText DisplayName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (Multiline = true))
	FText ItemDescription;

	UPROPERTY()
	class UInventorySystemC* Inventory;

	virtual void Use(class AGE_UECoddingCharacter* Character) PURE_VIRTUAL(UInventoryItemC, );

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class AGE_UECoddingCharacter* Character);
	
};
