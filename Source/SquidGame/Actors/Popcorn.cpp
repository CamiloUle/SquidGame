// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Popcorn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Characters/SquidGameCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
APopcorn::APopcorn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetMobility(EComponentMobility::Static);
	SetRootComponent(SceneComponent);*/

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BoxComponent"));
	SphereComponent->SetupAttachment(RootComponent);

	
}

void APopcorn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

// Called when the game starts or when spawned
void APopcorn::BeginPlay()
{
	Super::BeginPlay();
	
	FVector StartPosition = GetActorLocation();

	StartPosition.Z = 20;
	DrawDebugSphere(GetWorld(), StartPosition, 25, 10, FColor::Green, false, 3, 0, 2);

	MovementDirection = GetActorUpVector();

	RangeFunctionMap.Add(1, 1000.f);
	RangeFunctionMap.Add(2, 1200.f);
	RangeFunctionMap.Add(3, 1400.f);
	RangeFunctionMap.Add(4, 1600.f);
	RangeFunctionMap.Add(5, 1800.f);
	RangeFunctionMap.Add(6, 2000.f);

	float RandomSpeed = FMath::RandRange(1, 6);

	Speed = RangeFunctionMap.FindRef(RandomSpeed);
}

// Called every frame
void APopcorn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + -MovementDirection * Speed * DeltaTime);
}

