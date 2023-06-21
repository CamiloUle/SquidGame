// Fill out your copyright notice in the Description page of Project Settings.


#include "Bucket.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Actors/EvilPopcorn.h"
#include "Actors/Popcorn.h"


// Sets default values
ABucket::ABucket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);

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
	
}

// Called every frame
void ABucket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

