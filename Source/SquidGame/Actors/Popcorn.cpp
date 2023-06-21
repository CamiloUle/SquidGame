// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Popcorn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"


// Sets default values
APopcorn::APopcorn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BoxComponent"));
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APopcorn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APopcorn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

