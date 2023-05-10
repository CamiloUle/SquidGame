// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SquidGameGameState.generated.h"

/**
 * 
 */
UCLASS()
class SQUIDGAME_API ASquidGameGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	//ASquidGameGameState();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 KillCharacterCounter = 2;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float Timer = 2;

	UFUNCTION(BlueprintImplementableEvent)
	void OnEndSceneGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
