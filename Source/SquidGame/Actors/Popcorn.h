// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Popcorn.generated.h"

UCLASS()
class SQUIDGAME_API APopcorn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APopcorn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	class USphereComponent* SphereComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};