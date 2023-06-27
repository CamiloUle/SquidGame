// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RotatingPost.h"
#include "Actors/ActorLight.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Popcorn.h"
#include "Actors/EvilPopcorn.h"
#include "Components/BoxComponent.h"

// Sets default values
ARotatingPost::ARotatingPost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	//RootComponent = Mesh;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoXCollision"));
	BoxComponent->SetupAttachment(RootComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ARotatingPost::OnOverlapBegin);
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

}

void ARotatingPost::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) 
	{
		APopcorn* Popcorn = Cast<APopcorn>(OtherActor);
		AEvilPopcorn* EvilPopcorn = Cast<AEvilPopcorn>(OtherActor);

		if (Popcorn) 
		{
			Popcorn->Destroy();
			
		}
		if (EvilPopcorn) 
		{
			SpawnLocation = EvilPopcorn->GetActorLocation();

			SpawnLocation.Z = 1;
			OnSpawnEmitter();
			EvilPopcorn->Destroy();
		}
	}
}

void ARotatingPost::Rotated() 
{
	/*FRotator NewRotation = FRotator(0, Multiplier, 0);

	FQuat QuatRotation = FQuat(NewRotation);

	Mesh->AddLocalRotation(QuatRotation, false, 0, ETeleportType::None);*/
}

