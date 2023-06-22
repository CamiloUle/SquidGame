// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bucket.generated.h"

UCLASS()
class SQUIDGAME_API ABucket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABucket();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	class UBoxComponent* BoxComponent;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(Transient)
	int32 NumOfHits = 0;

	UPROPERTY(Transient, EditInstanceOnly)
	int32 BucketID = 0;

	UPROPERTY(Transient)
	class AEvilPopcorn* EvilPopcorn;

	UPROPERTY(Transient)
	class APopcorn* Popcorn;

	UPROPERTY(Transient)
	class ASquidGameCharacter* CharacterLeftPosition;

	UPROPERTY(Transient)
	class ASquidGameCharacter* CharacterRightPosition;

	UPROPERTY(Transient, EditInstanceOnly)
	float DistanceToAttach = 20.f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetUpCharacter();
	void AttachBucketToCharacter(int32 PlayerIndex);
};
