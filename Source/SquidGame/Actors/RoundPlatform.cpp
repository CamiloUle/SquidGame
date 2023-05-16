// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RoundPlatform.h"

// Sets default values
ARoundPlatform::ARoundPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ARoundPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoundPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoundPlatform::OnChangeMaterial()
{
	Mesh->SetMaterial(0, RedMaterial);
}

