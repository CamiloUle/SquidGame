// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/TimeManager.h"
#include "General/SquidGameGameState.h"
#include "TimerManager.h"
#include "Actors/DestroyablePlatform.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATimeManager::ATimeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADestroyablePlatform::StaticClass(), FoundActors);
	
	for (AActor* Actor : FoundActors) 
	{
		Platform = Cast<ADestroyablePlatform>(Actor);
	}
	

	GameState = GetWorld()->GetGameState<ASquidGameGameState>();
	OnUpdateTimer();
	Timer -= 1;
	GetWorldTimerManager().SetTimer(Delay, this, &ATimeManager::TimerToParty, 1.f, true);
}

void ATimeManager::TimerToParty()
{
	OnUpdateTimer();
	Timer -= 1;

	if (Timer <= 0 && GameState) 
	{
		Timer = 0;
		GameState->OnEndSceneGame();
	}
}

// Called every frame
void ATimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

