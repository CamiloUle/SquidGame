// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EvilPopcorn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Actors/Popcorn.h"

// Sets default values
AEvilPopcorn::AEvilPopcorn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BoxComponent"));
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEvilPopcorn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEvilPopcorn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

