// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RealoadableInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class URealoadableInterface : public UInterface
{
	GENERATED_BODY()
	
	
};

class IRealoadableInterface
{    
	GENERATED_BODY()

public:
	virtual bool CanReload_Implementation() PURE_VIRTUAL(IRealoadableInterface::CanReload_Implementation, return true; );
	virtual void Reload_Implementation() PURE_VIRTUAL(IRealoadableInterface::Reload_Implementation, );
};
