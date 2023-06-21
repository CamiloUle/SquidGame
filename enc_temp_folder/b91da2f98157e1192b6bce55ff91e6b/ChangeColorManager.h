// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChangeColorManager.generated.h"

UCLASS()
class SQUIDGAME_API AChangeColorManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChangeColorManager();

	bool bCharacterIsWalking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Delay = 3.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeFromMove = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPlayingAudio = false;

	UPROPERTY(Transient)
	FTimerHandle TimeToDestroyCharacter;

	virtual void KillCharacter();

	UPROPERTY(BlueprintReadWrite)
	class ASquidGameCharacter* TempCharacter;

	UPROPERTY(BlueprintReadWrite)
	class ASquidGameCharacter* CharacterLeftPosition;

	UPROPERTY(BlueprintReadWrite)
	class ASquidGameCharacter* CharacterRightPosition;

	UPROPERTY(BlueprintReadWrite)
	class AActorLight* ActorLight;

	UPROPERTY(BlueprintReadWrite)
	class AYoungHeeActor* YoungHeeActor;

	UPROPERTY(BlueprintReadWrite)
	class ASquidGameGameState* GameState;

	UPROPERTY(Transient)
	class ASquidGamePlayerController* TempPlayerController;

	UPROPERTY(Transient)
	class ASquidGamePlayerController* PlayerController1;

	UPROPERTY(Transient)
	class ASquidGamePlayerController* PlayerController2;

	UPROPERTY(Transient)
	TArray<AActor*> FoundCharacters;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
