// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/KillZone.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Characters/SquidGameCharacter.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "General/SquidGameGameState.h"
#include "General/SquidGamePlayerController.h"

#include "Engine/World.h"

// Sets default values
AKillZone::AKillZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AKillZone::OnOverlapBegin);
}



// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASquidGameCharacter::StaticClass(), FoundCharacters);

	for (auto Actor : FoundCharacters) 
	{
		ASquidGameCharacter* TempCharacter = Cast<ASquidGameCharacter>(Actor);

		if (TempCharacter) 
		{
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
}

// Called every frame
void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) 
	{
		Character = Cast<ASquidGameCharacter>(OtherActor);
		
		if(Character->CharacterIndex == 0)
		{
			CharacterLeftPosition->SetActorLocation(CharacterLeftPosition->SpawnLocation);

			FVector2D ScreenPosition(100.0f, 100.0f);
			float DisplayTime = 5.0f;

			FColor TextColor = FColor::Red;
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, DisplayTime, TextColor, "AAAA", false);
			}
		}
	}
}

