// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZone.generated.h"

UCLASS()
class SQUIDGAME_API AKillZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKillZone();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	class UBoxComponent* BoxComponent;

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
