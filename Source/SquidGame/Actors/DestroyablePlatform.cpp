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
#include "Containers/Map.h"
//#include "Containers/UnrealFunction.h"

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
	
	TimeToChangeColor = 1.f;

	SetNumberPlatform();
	
	ChangeStatePlatform();
	
	Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATimeManager::StaticClass());

	TimeManager = Cast<ATimeManager>(Actor);

	RangeFunctionMap.Add(1, [this]() { OnChangeHighZone(); });
	RangeFunctionMap.Add(2, [this]() { OnChangeMediumZone(); });
	RangeFunctionMap.Add(3, [this]() { OnChangeLowZone(); });
	RangeFunctionMap.Add(4, [this]() { OnChangeLowZone(); });
	RangeFunctionMap.Add(5, [this]() { OnChangeLowZone(); });
	RangeFunctionMap.Add(6, [this]() { OnChangeLowZone(); });
	RangeFunctionMap.Add(7, [this]() { OnChangeLowZone(); });
	RangeFunctionMap.Add(8, [this]() { OnChangeLowZone(); });
	RangeFunctionMap.Add(9, [this]() { OnChangeLowZone(); });
}

//Called every frame
void ADestroyablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

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
	if (TimeManager != nullptr)
	{
		if (TimeManager->Timer <= 45 && TimeManager->Timer >= 30)
		{
			TimeToChangeColor = 0.8f;
		}
		else if (TimeManager->Timer <= 30 && TimeManager->Timer >= 10)
		{
			TimeToChangeColor = 0.6f;
		}
		else if (TimeManager->Timer <= 10) 
		{
			TimeToChangeColor = 0.4f;
		}
	}

	SetActorEnableCollision(true);
	OnChangeIndexPlatform();
	
	TFunction<void()> ChangeZoneFunction = RangeFunctionMap.FindRef(RandomIndex);
	if (ChangeZoneFunction)
	{
		ChangeZoneFunction();
	}
	
	RandomIndex -= 1;
	if (RandomIndex <= -1)
	{
		//SetTimerToChangeMaterial();
		
		TimeToChangeColor = 1.5;

		Mesh->SetMaterial(0, RedMaterial);
		SetActorEnableCollision(false);
		SetNumberPlatform();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FallCue, GetActorLocation());
	}
	
	GetWorldTimerManager().SetTimer(Delay, this, &ADestroyablePlatform::ChangeNumberPlatform, TimeToChangeColor, false);
}

void ADestroyablePlatform::ChangeStatePlatform()
{
	GetWorldTimerManager().SetTimer(Delay, this, &ADestroyablePlatform::ChangeNumberPlatform, TimeToChangeColor, false);
}

void ADestroyablePlatform::ChageMaterialPlatoform()
{
	
	
}

void ADestroyablePlatform::SetTimerToChangeMaterial()
{
	FTimerHandle TimerHandle;
	float Timer = 1.2f;
	RandomIndex = 0;
	GetWorldTimerManager().SetTimer(TimerHandle,this, &ADestroyablePlatform::ChageMaterialPlatoform, Timer, true);
}



