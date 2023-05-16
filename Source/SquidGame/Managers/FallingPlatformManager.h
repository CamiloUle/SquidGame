// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingPlatformManager.generated.h"

UCLASS()
class SQUIDGAME_API AFallingPlatformManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallingPlatformManager();

	UPROPERTY(Transient)
	class ARoundPlatform* RoundPlatform;

	UPROPERTY(Transient)
	TArray<AActor*> FoundActors;

	UPROPERTY(Transient)
	FTimerHandle TimerHandle;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ChangeStatePlatform();
	void ChangeMaterial();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
