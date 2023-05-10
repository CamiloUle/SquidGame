// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YoungHeeActor.generated.h"

UCLASS()
class SQUIDGAME_API AYoungHeeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYoungHeeActor();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRotationActorRight();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRotationActorLeft();

	UPROPERTY(Transient)
	class AActorLight* ActorLight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
