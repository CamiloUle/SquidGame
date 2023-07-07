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

	if (bIsStaticCameraMode) 
	{
		FVector CamerLocation = GetActorLocation();
		SetActorLocation(CamerLocation);
	}
}

void ACharacterCameraActor::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
	if (!bIsStaticCameraMode)
	{	
		SetCameraLocation();	
	}
}

void ACharacterCameraActor::SetPlayerCharacters()
{
	
}

void ACharacterCameraActor::SetCameraLocation()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASquidGameCharacter::StaticClass(), FoundCharacters);

	ASquidGameCharacter* CharacterFocused = NULL;
	float MaxDistance = -99999999999.f;

	for (auto Actor : FoundCharacters)
	{
		SquidGameCharacter = Cast<ASquidGameCharacter>(Actor);

		if (SquidGameCharacter && SquidGameCharacter->GetActorLocation().X > MaxDistance)
		{
			MaxDistance = SquidGameCharacter->GetActorLocation().X;

			CharacterFocused = SquidGameCharacter;
		}
	}

	if (CharacterFocused)
	{
		FVector NewCameraLocation = GetActorLocation();
		NewCameraLocation.X = CharacterFocused->GetActorLocation().X - XGap;

		SetActorLocation(NewCameraLocation);
	}

}
