// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ActorLight.h"
#include "Characters/SquidGameCharacter.h"
#include "Actors/YoungHeeActor.h"
#include "Actors/ActorLight.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AActorLight::AActorLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorLight::BeginPlay()
{
	Super::BeginPlay();
	

	YoungHee = Cast<AYoungHeeActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AYoungHeeActor::StaticClass()));
}

// Called every frame
void AActorLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeFromMove -= DeltaTime;
	
	/*if (bIsKillCharacter && YoungHee)
	{
		Delay -= DeltaTime; 

		if (Delay <= 0.0f) 
		{
			bIsKillCharacter = false;
			if (!bIsKillCharacter) 
			{
				TimeFromMove = 5.0f;
			}
			OnChangeGreenColor();
			YoungHee->OnRotationActorLeft();
			Delay = 3.5f;
		}
	}*/
}

void AActorLight::PlaySound() 
{

}






