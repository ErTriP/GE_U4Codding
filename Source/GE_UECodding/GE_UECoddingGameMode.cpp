// Copyright Epic Games, Inc. All Rights Reserved.

#include "GE_UECoddingGameMode.h"
#include "GE_UECoddingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGE_UECoddingGameMode::AGE_UECoddingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
