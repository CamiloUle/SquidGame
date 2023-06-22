// Fill out your copyright notice in the Description page of Project Settings.


#include "Bucket.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Actors/EvilPopcorn.h"
#include "Actors/Popcorn.h"
#include "Characters/SquidGameCharacter.h"


// Sets default values
ABucket::ABucket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	//BoxComponent->SetupAttachment(RootComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABucket::OnOverlapBegin);
}

void ABucket::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) 
	{
		EvilPopcorn = Cast<AEvilPopcorn>(OtherActor);
		Popcorn = Cast<APopcorn>(OtherActor);

		if (Popcorn != nullptr) 
		{
			NumOfHits += 1;
		}
		else if (EvilPopcorn != nullptr) 
		{
			NumOfHits -= 1;
		}
	}
}

// Called when the game starts or when spawned
void ABucket::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundCharacters;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASquidGameCharacter::StaticClass(), FoundCharacters);

	for (auto Actor : FoundCharacters) 
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
	}
}

// Called every frame
void ABucket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SetNewPosition();
}

void ABucket::SetNewPosition()
{
	//float DistanceToAttach = 20.f;

	if (BucketID == 0 && CharacterLeftPosition)
	{
		const float DistanceSqrPlayer1 = ((CharacterLeftPosition->GetActorLocation() - GetActorLocation()).SizeSquared2D());

		if (DistanceSqrPlayer1 <= (DistanceToAttach * DistanceToAttach)) 
		{
			SetActorRelativeLocation((CharacterLeftPosition->GetActorLocation()));
		}
	}
	
	if(BucketID == 1 && CharacterRightPosition)
	{
		const float DistanceSqrPlayer2 = ((CharacterRightPosition->GetActorLocation() - GetActorLocation()).SizeSquared2D());

		if (DistanceSqrPlayer2 <= (DistanceToAttach * DistanceToAttach))
		{
			SetActorRelativeLocation(CharacterRightPosition->GetActorLocation());
		}
	}

	
}

