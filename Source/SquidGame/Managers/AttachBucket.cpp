// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/AttachBucket.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Bucket.h"
#include "Characters/SquidGameCharacter.h"

// Sets default values
AAttachBucket::AAttachBucket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAttachBucket::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> FoundActors;
	
	
}

// Called every frame
void AAttachBucket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SetNewPosition();
}

void AAttachBucket::SetNewPosition()
{
	
}

