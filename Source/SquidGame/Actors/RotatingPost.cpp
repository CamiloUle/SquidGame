// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RotatingPost.h"
#include "Actors/ActorLight.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Popcorn.h"
#include "Actors/Popcorn.h"

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
	//PopCorn = nullptr;

	//SpawnDecal();
	TimeToSpawnDecal();
}

// Called every frame
void ARotatingPost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Rotated();

	
	//SpawnDecal();
}

void ARotatingPost::Rotated() 
{
	FRotator NewRotation = FRotator(0, Multiplier, 0);

	FQuat QuatRotation = FQuat(NewRotation);

	Mesh->AddLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void ARotatingPost::SpawnDecal()
{
	FVector End = GetActorLocation();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APopcorn::StaticClass(), FoundActors);

	for (auto Actor : FoundActors) 
	{
		PopCorn = Cast<APopcorn>(Actor);
		if (PopCorn) 
		{
			FVector Start = PopCorn->GetActorLocation();

			FHitResult HitResult;
			FCollisionQueryParams QueryParams;

			GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, QueryParams);

			if (HitResult.bBlockingHit)
			{
				FVector ImpactPoint = HitResult.ImpactNormal;
				DrawDebugSphere(GetWorld(), ImpactPoint, 20, 20, FColor::Red, true, -1,0,2);
			}
		}
	}
}

void ARotatingPost::TimeToSpawnDecal()
{
	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARotatingPost::SpawnDecal, 1, true);
}

