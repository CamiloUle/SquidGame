// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

UCLASS()
class SQUIDGAME_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeManager();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int32 Timer;

	//float TimerToChangeColor = 1;

	UPROPERTY()
	FTimerHandle Delay;

	UPROPERTY(Transient)
	class ASquidGameGameState* GameState;

	UPROPERTY(Transient)
	class ADestroyablePlatform* Platform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TimerToParty();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateTimer();

};
