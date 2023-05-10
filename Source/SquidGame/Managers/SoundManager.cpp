// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/SoundManager.h"
#include "Actors/DestroyablePlatform.h"
#include "Managers/TimeManager.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/GameEngine.h"
#include "Sound/SoundCue.h"


// Sets default values
ASoundManager::ASoundManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
	Super::BeginPlay();
	
	Platform = Cast<ADestroyablePlatform>(UGameplayStatics::GetActorOfClass(GetWorld(), ADestroyablePlatform::StaticClass()));

}

// Called every frame
void ASoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//PlayCountDownSound();
}

void ASoundManager::PlayCountDownSound()
{
	if (Platform != nullptr) 
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), CountDownCue, Platform->GetActorLocation());

		if (Platform->RandomIndex <= -1) 
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FallCue, Platform->GetActorLocation());
		}
	}
}