// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DestroyablePlatform.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Characters/SquidGameCharacter.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TimeManager.h"
#include "Engine/GameEngine.h"
#include "Sound/SoundCue.h"

// Sets default values
ADestroyablePlatform::ADestroyablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh"); 
	RootComponent = Mesh;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADestroyablePlatform::BeginPlay()
{
	Super::BeginPlay();
	
	SetNumberPlatform();

	GetWorldTimerManager().SetTimer(Delay, this, &ADestroyablePlatform::ChangeNumberPlatform, TimeToChangeColor, true);

	Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());

	TimeManager = Cast<ATimeManager>(Actor);
}

//Called every frame
void ADestroyablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChangeStatePlatform();

}
void ADestroyablePlatform::SetNumberPlatform()
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Yellow, TEXT("Some debug message!"));
	}*/
	
	RandomIndex = FMath::RandRange(1, 9);
}

void ADestroyablePlatform::ChangeNumberPlatform()
{
	

	SetActorEnableCollision(true);
	OnChangeIndexPlatform();
	
	RandomIndex -= 1;
	
	FString String = FString::SanitizeFloat(TimeToChangeColor);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, *String);
	}

	if (RandomIndex >= 6 && RandomIndex <= 9)
	{
		OnChangeLowZone();
	}

	if (RandomIndex >= 4 && RandomIndex <= 6)
	{
		OnChangeMediumZone();
	}

	if (RandomIndex >= 1 && RandomIndex <= 3)
	{
		OnChangeHighZone();
	}
	
	if (RandomIndex <= -1)
	{
		Mesh->SetMaterial(0, RedMaterial);
		SetActorEnableCollision(false);
		SetNumberPlatform();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FallCue, GetActorLocation());
	}
}

void ADestroyablePlatform::ChangeStatePlatform()
{
	if (TimeManager != nullptr) 
	{
		if (TimeManager->Timer <= 20 && TimeManager->Timer >= 10)
		{
			TimeToChangeColor = 0.75f;
		}
		else if (TimeManager->Timer <= 10) 
		{
			TimeToChangeColor = 0.5f;
		}
	}
}



