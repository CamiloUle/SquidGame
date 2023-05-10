// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/YoungHeeActor.h"
#include "Actors/ActorLight.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AYoungHeeActor::AYoungHeeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AYoungHeeActor::BeginPlay()
{
	Super::BeginPlay();
	
	//ActorLight = Cast<AActorLight>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorLight::StaticClass()));
}

// Called every frame
void AYoungHeeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

