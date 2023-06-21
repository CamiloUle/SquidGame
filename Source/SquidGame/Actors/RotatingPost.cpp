// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RotatingPost.h"
#include "Actors/ActorLight.h"
#include "Kismet/GameplayStatics.h"

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
	
	ActorLight = Cast<AActorLight>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorLight::StaticClass()));
}

// Called every frame
void ARotatingPost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotated();

	Timer -= DeltaTime;

}

void ARotatingPost::Rotated() 
{
	FRotator NewRotation = FRotator(0, Multiplier, 0);

	FQuat QuatRotation = FQuat(NewRotation);

	Mesh->AddLocalRotation(QuatRotation, false, 0, ETeleportType::None);

	if (Timer <= 50.f)
	{
		Multiplier = Multiplier * 2;
	}
}

