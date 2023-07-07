// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/ChangeColorManager.h"
#include "Managers/TimeManager.h"
#include "Characters/SquidGameCharacter.h"
#include "Actors/ActorLight.h"
#include "Actors/YoungHeeActor.h"
#include "General/SquidGameGameState.h"
#include "Kismet/GameplayStatics.h"
#include "General/SquidGamePlayerController.h"
#include "Engine/GameEngine.h"
#include "Sound/SoundCue.h"
#include "TimerManager.h"


// Sets default values
AChangeColorManager::AChangeColorManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//static ConstructorHelpers::FObjectFinder<USoundCue> Sound(TEXT("''"));

}


// Called when the game starts or when spawned
void AChangeColorManager::BeginPlay()
{
	Super::BeginPlay();

	GameState = GetWorld()->GetGameState<ASquidGameGameState>();

	ActorLight = Cast<AActorLight>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorLight::StaticClass()));
	YoungHeeActor = Cast<AYoungHeeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AYoungHeeActor::StaticClass()));
	TimeManager = Cast<ATimeManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass()));

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASquidGameCharacter::StaticClass(), FoundCharacters);

	
	for (auto Actor : FoundCharacters) 
	{
		TempCharacter = Cast<ASquidGameCharacter>(Actor);

		if (TempCharacter) 
		{
			if (TempCharacter->CharacterIndex == 0) 
			{
				CharacterLeftPosition = TempCharacter;
				
			}
			else if (TempCharacter->CharacterIndex == 1)
			{
				CharacterRightPosition = TempCharacter;
				
			}
		}
	}
}

// Called every frame
void AChangeColorManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActorLight && YoungHeeActor)
	{
		if (bIsPlayingAudio) 
		{
			ActorLight->OnChangeGreenColor();
			YoungHeeActor->OnRotationActorLeft();
		}
		else if (!bIsPlayingAudio) 
		{
			ActorLight->OnChangeRedColor();
			YoungHeeActor->OnRotationActorRight();

			//KillCharacter();
		}
	}
}

void AChangeColorManager::KillCharacter() 
{
	for (auto Actor : FoundCharacters)
	{
		if (CharacterLeftPosition->MovementDirection.Size2D() > 0 || CharacterLeftPosition->bIsJumping)
		{
			CharacterLeftPosition->bIsCharacterDead = true;
			CharacterLeftPosition->OnKillCharacter();
		}
		else if (CharacterRightPosition->MovementDirection.Size2D() > 0 || CharacterRightPosition->bIsJumping)
		{
			CharacterRightPosition->bIsCharacterDead = true;
			CharacterRightPosition->OnKillCharacter();
		}

		if (GameState && TimeManager)
		{
			if (CharacterRightPosition->bIsCharacterDead && CharacterLeftPosition->bIsCharacterDead)
			{
				GameState->OnEndSceneGame();
				TimeManager->Timer = 0;
			}
		}
	}
}






