// Copyright Epic Games, Inc. All Rights Reserved.

#include "HideAndSeekGameMode.h"
#include "HideAndSeekCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHideAndSeekGameMode::AHideAndSeekGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
