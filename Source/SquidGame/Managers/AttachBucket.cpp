// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/AttachBucket.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Bucket.h"
#include "Characters/SquidGameCharacter.h"

// Sets default values
AAttachBucket::AAttachBucket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAttachBucket::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> FoundActors;
	

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASquidGameCharacter::StaticClass(), FoundActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABucket::StaticClass(), FoundBuckets);

	for (auto Actor : FoundActors)
	{
		ASquidGameCharacter* TempCharacter = Cast<ASquidGameCharacter>(Actor);

		if (TempCharacter->CharacterIndex == 0)
		{
			CharacterLeftPosition = TempCharacter;
		}
		else if (TempCharacter->CharacterIndex == 1)
		{
			CharacterRightPosition = TempCharacter;
		}

		ABucket* TempBucket = Cast<ABucket>(Actor);

		if (TempBucket->BucketID == 0)
		{
			BucketLeftPosition = TempBucket;
		}
		else if (TempBucket->BucketID == 1)
		{
			BucketRightPosition = TempBucket;
		}
	}

	for (auto Actor : FoundActors)
	{
		
	}
}

// Called every frame
void AAttachBucket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetNewPosition();
}

void AAttachBucket::SetNewPosition()
{
	if (BucketLeftPosition != nullptr && CharacterRightPosition != nullptr)
	{
		const float DistanceSqrtP1 = (CharacterRightPosition->GetActorLocation() - BucketLeftPosition->GetActorLocation()).SizeSquared2D();

		if (DistanceSqrtP1 <= (BucketLeftPosition->DistanceToAttach * BucketLeftPosition->DistanceToAttach)) 
		{
			BucketLeftPosition->SetActorLocation(CharacterRightPosition->GetActorLocation());
		}
	}
	
	if (BucketLeftPosition != nullptr && CharacterLeftPosition != nullptr)
	{
		const float DistanceSqrtP2 = (CharacterLeftPosition->GetActorLocation() - BucketLeftPosition->GetActorLocation()).SizeSquared2D();

		if (DistanceSqrtP2 <= (BucketLeftPosition->DistanceToAttach * BucketLeftPosition->DistanceToAttach))
		{
			BucketLeftPosition->SetActorLocation(CharacterLeftPosition->GetActorLocation());
		}
	}

	
	for (auto Actor : FoundBuckets) 
	{
		ABucket* Buckets = Cast<ABucket>(Actor);

		


		if (Buckets && Buckets->BucketID == 0) 
		{
			const float DistanceSqrtP1 = (CharacterRightPosition->GetActorLocation() - Buckets->GetActorLocation()).SizeSquared2D();
		}
	}
}

