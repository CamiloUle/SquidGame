// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/FallingPlatformManager.h"
#include "Actors/RoundPlatform.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFallingPlatformManager::AFallingPlatformManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFallingPlatformManager::BeginPlay()
{
	Super::BeginPlay();
	
	

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFallingPlatformManager::ChangeStatePlatform, 5.f, true);
}

void AFallingPlatformManager::ChangeStatePlatform()
{
	
	int RandIndexPlatform = FMath::RandRange(1,4);
	for (auto Actor : FoundActors)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoundPlatform::StaticClass(), FoundActors);

		RoundPlatform = Cast<ARoundPlatform>(Actor);
		if (RoundPlatform != nullptr)
		{
			if (RandIndexPlatform == RoundPlatform->FallingIndex)
			{
				RoundPlatform->OnChangeMaterial();
			}
		}
	}
	
}

void AFallingPlatformManager::ChangeMaterial()
{
}

// Called every frame
void AFallingPlatformManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

