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
	
	FVector StartPosition = GetActorLocation();

	StartPosition.Z = 20;
	DrawDebugSphere(GetWorld(), StartPosition, 25, 10, FColor::Red, false, 2, 0, 2);


	MovementDirection = GetActorUpVector();

	RangeFunctionMap.Add(1, 1300.f);
	RangeFunctionMap.Add(2, 1600.f);
	RangeFunctionMap.Add(3, 1900.f);
	

	float RandomSpeed = FMath::RandRange(1, 3);

	Speed = RangeFunctionMap.FindRef(RandomSpeed);
}

// Called every frame
void AEvilPopcorn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + -MovementDirection * Speed * DeltaTime);
}

