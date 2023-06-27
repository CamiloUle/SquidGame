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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnActor(AActor* ActorTypeToSpawn, TSubclassOf<AActor>ClassToSpawn);
	
	void ScheduleActorSpawn();

	void ScheduleEvilActorSpawn();

private:

	UFUNCTION()
	void SpawnActorSchedule();

	UFUNCTION()
	void SpawnEvilActorSchedule();

public: 

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* SpawnBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<AActor> EvilActorSpawn;

	UPROPERTY(Transient)
	class APopcorn* Popcorn;

	UPROPERTY(Transient)
	class AEvilPopcorn* EvilPopcorn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldSpawn = true;

	//Timer To spawn

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomSpawnTimeOffset = 0;

	UPROPERTY(Transient)
	int32 NumOfRoundToSpawnActors = 0;

private:

	
};
