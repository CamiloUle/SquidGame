// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CharacterCameraActor.h"
#include "Characters/SquidGameCharacter.h"
#include "General/SquidGamePlayerController.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "General/SquidGameGameState.h"
#include "Camera/CameraComponent.h"
#include "Engine/GameEngine.h"
#include "GameFrameWork/Actor.h"


ACharacterCameraActor::ACharacterCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterCameraActor::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASquidGameCharacter::StaticClass(), FoundCharacters);

	if (bIsStaticCameraMode) 
	{
		FVector CamerLocation = GetActorLocation();
		SetActorLocation(CamerLocation);
	}

	for (auto Actor : FoundCharacters)
	{
		SquidGameCharacter = Cast<ASquidGameCharacter>(Actor);

		if (SquidGameCharacter)
		{
			if (SquidGameCharacter->CharacterIndex == 0)
			{
				CharacterLeftPosition = SquidGameCharacter;
			}
			else if (SquidGameCharacter->CharacterIndex == 1)
			{
				CharacterRightPosition = SquidGameCharacter;
			}
		}
	}
}

void ACharacterCameraActor::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
	if (!bIsStaticCameraMode) 
	{
		FVector NewCameraLocation = GetActorLocation();

		ASquidGameCharacter* ClosestCharacter = NULL;

		if (CharacterLeftPosition->GetActorLocation().X < CharacterRightPosition->GetActorLocation().X)
		{
			ClosestCharacter = CharacterLeftPosition;
		}
		else
		{
			ClosestCharacter = CharacterRightPosition;
		}

		if (ClosestCharacter)
		{
			NewCameraLocation.X = ClosestCharacter->GetActorLocation().X - XGap;
			SetActorLocation(NewCameraLocation);
		}

		if (CharacterLeftPosition->bIsCharacterDead)
		{
			ClosestCharacter = CharacterRightPosition;
		}
		else if (CharacterRightPosition->bIsCharacterDead)
		{
			ClosestCharacter = CharacterLeftPosition;
		}

		if (ClosestCharacter)
		{
			NewCameraLocation.X = ClosestCharacter->GetActorLocation().X - XGap;
			SetActorLocation(NewCameraLocation);
		}
	}
}