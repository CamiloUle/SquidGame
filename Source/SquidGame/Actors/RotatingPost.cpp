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


	Dimensions = FVector(0, 300, 0);
	AxisVector = FVector(0, 0, 1);
	Multiplier = 50.f;
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
}

void ARotatingPost::Rotated() 
{
	FRotator NewRotation = FRotator(0, 0, Multiplier);

	FQuat QuatRotation = FQuat(NewRotation);

	Mesh->AddLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void ARotatingPost::RotateAroundOtherActor() 
{
	FVector NewLocation = FVector(0, 0, 800);

	FVector Radius = FVector(200, 0, 0);

	AngleAxis++;

	if (AngleAxis >= 360.0f)
	{
		AngleAxis = 0;
	}

	FVector RotateValue = Radius.RotateAngleAxis(AngleAxis, FVector(0, 0, 0));

	NewLocation.X += RotateValue.X;
	NewLocation.Y += RotateValue.Y;
	NewLocation.Z += RotateValue.Z;

	SetActorLocation(NewLocation);

	/*FRotator NewRotation = FRotator(0, 0, AngleAxis);

	FQuat QuatRotation = FQuat(NewRotation);

	SetActorLocationAndRotation(NewLocation, QuatRotation, false, 0, ETeleportType::None);*/
}