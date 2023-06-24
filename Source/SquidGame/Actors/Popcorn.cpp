// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Popcorn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Characters/SquidGameCharacter.h"
#include "Components/SceneComponent.h"


// Sets default values
APopcorn::APopcorn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetMobility(EComponentMobility::Static);
	SetRootComponent(SceneComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BoxComponent"));
	SphereComponent->SetupAttachment(SceneComponent);
}

void APopcorn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
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

