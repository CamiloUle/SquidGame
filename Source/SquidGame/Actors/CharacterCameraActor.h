// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CharacterCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class SQUIDGAME_API ACharacterCameraActor : public ACameraActor
{
	GENERATED_BODY()
	
public:

	ACharacterCameraActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Transient)
	float Speed = 5.0f;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float XGap = 700;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	bool bIsStaticCameraMode = false;
	
	float DistanceToCharacterLeftPosition;
	float DistanceToCharacterRightPosition;

	FVector LeftCharacter;
	FVector RightCharacter;
	
	UPROPERTY(Transient)
	TArray<AActor* > FoundCharacters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ASquidGameCharacter* SquidGameCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ASquidGameCharacter* CharacterLeftPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ASquidGameCharacter* CharacterRightPosition;

	UFUNCTION(BlueprintCallable)
	void SetPlayerCharacters();

	void SetCameraLocation();
};
