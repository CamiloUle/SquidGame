// Copyright Epic Games, Inc. All Rights Reserved.

#include "General/SquidGameGameMode.h"
#include "Characters/SquidGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASquidGameGameMode::ASquidGameGameMode()
{
	// set default pawn class to our Blueprinted character
	/**static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}
