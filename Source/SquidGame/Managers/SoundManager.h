// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundManager.generated.h"

UCLASS()
class SQUIDGAME_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();

	UPROPERTY(Transient)
	class ADestroyablePlatform* Platform;

	UPROPERTY(Transient, EditAnyWhere)
	class USoundCue* CountDownCue;

	UPROPERTY(Transient, EditAnyWhere)
	class USoundCue* FallCue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlayCountDownSound();

};
