// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SquidGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SQUIDGAME_API ASquidGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASquidGamePlayerController();
	
	virtual void Tick(float DeltaTime) override;
	void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void InputMovementXP1(float Value);
	void InputMovementYP1(float Value);
	void InputJumpXP1();
	
	void InputMovementXP2(float Value);
	void InputMovementYP2(float Value);
	void InputJumpXP2();
	
	void SetStunStatePlayer1();
	void SetStunStatePlayer2();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ASquidGameCharacter* CharacterLeftPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ASquidGameCharacter* CharacterRightPosition;

	UPROPERTY(Transient)
	TArray<AActor* > FoundCharacters;

	UPROPERTY(Transient)
	AActor* ActorCharacters;
};
