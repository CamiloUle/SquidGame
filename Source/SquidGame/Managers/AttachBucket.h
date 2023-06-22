// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttachBucket.generated.h"

UCLASS()
class SQUIDGAME_API AAttachBucket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttachBucket();

	UPROPERTY(Transient)
	class ASquidGameCharacter* CharacterLeftPosition;

	UPROPERTY(Transient)
	class ASquidGameCharacter* CharacterRightPosition;


	UPROPERTY(Transient)
	class ABucket* BucketLeftPosition;

	UPROPERTY(Transient)
	class ABucket* BucketRightPosition;

	UPROPERTY(Transient)
	TArray<AActor*> FoundBuckets;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetNewPosition();
};
