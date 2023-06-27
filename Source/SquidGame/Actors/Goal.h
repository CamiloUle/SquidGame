// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UCLASS()
class SQUIDGAME_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoal();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	class UBoxComponent* BoxComponent;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 OverlapGoalCounter = 0;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	bool bIsWantKillCharacter = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	bool bIsSetNewPosition = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	bool bIsWantWonCharacter = false;

	UPROPERTY(Transient)
	TArray<AActor*> FoundCharacters;

	UPROPERTY(Transient)
	class ASquidGameGameState* GameState;

	UPROPERTY(Transient)
	class ASquidGamePlayerController* PlayerController;

	UPROPERTY(Transient)
	class ASquidGameCharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ASquidGameCharacter* CharacterLeftPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ASquidGameCharacter* CharacterRightPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 CounterLifeplayer1 = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 CounterLifeplayer2 = 3;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
