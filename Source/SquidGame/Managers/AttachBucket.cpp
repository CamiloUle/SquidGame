// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/AttachBucket.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Bucket.h"
#include "Characters/SquidGameCharacter.h"
#include "Actors/EvilPopcorn.h"
#include "Actors/Popcorn.h"
#include "NavigationSystem.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include <Kismet/KismetMathLibrary.h>
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AAttachBucket::AAttachBucket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxToSpawn"));
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void AAttachBucket::BeginPlay()
{
	Super::BeginPlay();
	
	ScheduleActorSpawn();
	
	
	ScheduleEvilActorSpawn();
	
	
}

// Called every frame
void AAttachBucket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}

void AAttachBucket::SpawnActor(AActor* ActorTypeToSpawn, TSubclassOf<AActor>ClassToSpawn)
{
	int32 RandOfActorsToSpawn = FMath::RandRange(0, 5);

	//for (int32 i = 0; i <= RandOfActorsToSpawn; i++)
	{
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());

		FVector SpawnPosition = BoxBounds.Origin;

		/*FString VectorToString = BoxBounds.Origin.ToString();
		UE_LOG(LogTemp, Log, TEXT("Vector: %s"), *VectorToString);
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, VectorToString, false);*/

		SpawnPosition.X += -BoxBounds.BoxExtent.X + 3 * BoxBounds.BoxExtent.X * FMath::FRand();
		SpawnPosition.Y += -BoxBounds.BoxExtent.Y + 3 * BoxBounds.BoxExtent.Y * FMath::FRand();
		SpawnPosition.Z += -BoxBounds.BoxExtent.Z + 3 * BoxBounds.BoxExtent.Z * FMath::FRand();

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = this;
		SpawnParam.bNoFail = true;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ActorTypeToSpawn = GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnPosition, FRotator::ZeroRotator, SpawnParam);
		
		if (!ActorTypeToSpawn)
			return;
	}
}

void AAttachBucket::ScheduleActorSpawn()
{
	float RandomTimeToSpawnActor = FMath::RandRange(1, 4);

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAttachBucket::SpawnActorSchedule, RandomTimeToSpawnActor, false);
}


void AAttachBucket::SpawnActorSchedule()
{
	Popcorn = nullptr;

	int32 RandOfActorsToSpawn = FMath::RandRange(3, 6);

	for (int32 i = 0; i <= RandOfActorsToSpawn; i++)
	{
		SpawnActor(Popcorn, ActorToSpawn);
		
	}

	ScheduleActorSpawn();
}

void AAttachBucket::ScheduleEvilActorSpawn()
{
	float RandomTimeToSpawnActor = FMath::RandRange(4, 6);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAttachBucket::SpawnEvilActorSchedule, RandomTimeToSpawnActor, false);
}
	

void AAttachBucket::SpawnEvilActorSchedule()
{
	EvilPopcorn = nullptr;

	int32 RandOfActorsToSpawn = FMath::RandRange(3, 5);

	for (int32 i = 0; i <= RandOfActorsToSpawn; i++)
	{
		SpawnActor(EvilPopcorn, EvilActorSpawn);
		
	}
	ScheduleEvilActorSpawn();
}