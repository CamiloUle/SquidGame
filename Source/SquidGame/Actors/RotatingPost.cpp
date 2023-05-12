// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RotatingPost.h"

// Sets default values
ARotatingPost::ARotatingPost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ARotatingPost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingPost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = FRotator(0, 0, SpeedRotation);

	FQuat QuatRotation = FQuat(NewRotation);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

