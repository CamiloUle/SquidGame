// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorLight.generated.h"

UCLASS()
class SQUIDGAME_API AActorLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorLight();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsKillCharacter = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Delay = 7.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeFromMove = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsPlayingAudio = false;

	UPROPERTY(Transient)
	TArray<AActor*> FoundCharacters;

	UPROPERTY(Transient)
	class ASquidGameCharacter* Characters;

	UPROPERTY(Transient)
	class AActorLight* Light;

	UPROPERTY(Transient)
	class AYoungHeeActor* YoungHee;


	

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeRedColor();

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeGreenColor();
	
	UFUNCTION(BlueprintCallable, Category = "Sound")
	virtual void PlaySound();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
