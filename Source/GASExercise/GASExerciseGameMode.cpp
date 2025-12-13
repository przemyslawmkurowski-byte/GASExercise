// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASExerciseGameMode.h"
#include "GASExerciseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGASExerciseGameMode::AGASExerciseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
