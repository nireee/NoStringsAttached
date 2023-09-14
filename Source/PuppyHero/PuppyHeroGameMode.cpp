// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuppyHeroGameMode.h"
#include "PuppyHeroCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuppyHeroGameMode::APuppyHeroGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
