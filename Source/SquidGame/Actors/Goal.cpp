// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Goal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Characters/SquidGameCharacter.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "General/SquidGameGameState.h"
#include "General/SquidGamePlayerController.h"

#include "Engine/World.h"

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();

	GameState = GetWorld()->GetGameState<ASquidGameGameState>();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASquidGameCharacter::StaticClass(), FoundCharacters);

	for (auto Actor : FoundCharacters) 
	{
		//ASquidGameCharacter* TempCharacter = Cast<ASquidGameCharacter>(Actor);

		Character = Cast<ASquidGameCharacter>(Actor);

		if (Character)
		{
			if (Character->CharacterIndex == 0)
			{
				CharacterLeftPosition = Character;
			}
			else if (Character->CharacterIndex == 1)
			{
				CharacterRightPosition = Character;
			}
		}
	}

	PlayerController = Cast<ASquidGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GameState) 
	{
		if (OverlapGoalCounter >= 2)
		{
			GameState->OnEndSceneGame();
		}

		if ((OverlapGoalCounter == 1 && CharacterRightPosition->bIsCharacterDead)
			|| (OverlapGoalCounter == 1 && CharacterLeftPosition->bIsCharacterDead))
		{
			GameState->OnEndSceneGame();
		}

		if (CounterLifeplayer1 <= 0 || CounterLifeplayer2 <= 0) 
		{
			GameState->OnEndSceneGame();
		}
	}	
}

void AGoal::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (OtherActor && OtherActor != this)
	{
		Character = Cast<ASquidGameCharacter>(OtherActor);

		if (Character && GEngine)
		{
			if (bIsWantWonCharacter)
			{
				OverlapGoalCounter++;
				if (Character->CharacterIndex == 0 && PlayerController != nullptr)
				{
					//GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::Yellow, FString("Toque el triguer"), true);

					Character->OnCrossGoal();
					Character->bIscharacterOverlapGoal = true;
				}
				else if (Character->CharacterIndex == 1 && PlayerController != nullptr)
				{
					//GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::Red, FString("Toque el triguer"), true);

					Character->OnCrossGoal();
					Character->bIscharacterOverlapGoal = true;
				}
			}

			if (bIsWantKillCharacter)
			{
				OverlapGoalCounter++;

				if (Character->CharacterIndex == 0)
				{	
					Character->OnKillCharacter();
					Character->bIscharacterOverlapGoal = true;
				}
				else if (Character->CharacterIndex == 1) 
				{
					Character->OnKillCharacter();
					Character->bIscharacterOverlapGoal = true;
				}
			}

			if (bIsSetNewPosition)
			{
				if (Character->CharacterIndex == 0)
				{
					Character->SetActorLocation(Character->SpawnLocation);
					CounterLifeplayer1 -= 1;
				}
				else if (Character->CharacterIndex == 1)
				{
					Character->SetActorLocation(Character->SpawnLocation);
					CounterLifeplayer2 -= 1;
				}
			}
		}
	}
} 