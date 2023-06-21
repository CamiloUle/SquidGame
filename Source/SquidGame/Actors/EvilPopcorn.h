// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EvilPopcorn.generated.h"

UCLASS()
class SQUIDGAME_API AEvilPopcorn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEvilPopcorn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	class USphereComponent* SphereComponent;


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
