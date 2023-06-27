// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SquidGameCharacter.generated.h"

UCLASS(config=Game)
class ASquidGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	 //Follow camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	ASquidGameCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	class UStaticMeshComponent* StaticMesh;

public:

	FVector InputMovement;
	FVector LastMovementDirection;
	FVector SpawnLocation; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector MovementDirection;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int32 CharacterIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 RandomCharacterID = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 NumOfHits = 0;

	UPROPERTY(Transient)
	bool bIsCharacterDead = false;
	
	UPROPERTY(Transient)
	bool bIscharacterOverlapGoal = false;

	UPROPERTY(Transient)
	bool bIsCharacterAplyStun = false;

	UPROPERTY(Transient)
	bool bIsJumping = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	bool bIsSetBucket = false;
	
	UPROPERTY(Transient)
	float StunCooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SetStunCooldown = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StunRange = 500.0f;

	UPROPERTY(Transient)
	float TimeToStun = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SetTimeToStun = 0.0f;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;


public:

	UPROPERTY(Transient)
	class AEvilPopcorn* EvilPopcorn;

	UPROPERTY(Transient)
	class APopcorn* Popcorn;

	UPROPERTY(Transient)
	class ACharacterCameraActor* CameraPosition;

	UPROPERTY(Transient)
	class AYoungHeeActor* YoungHee;

	UPROPERTY(Transient)
	class AActorLight* Light;

	UPROPERTY(Transient)
	class ASquidGameGameState* GameState;

	
protected:
	// APawn interface
	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void PlayStunSound();

	UFUNCTION(BlueprintImplementableEvent)
	void OnKillCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSpawnSound();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCrossGoal();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetCounter();

	UFUNCTION()
	void RemovePlayerInput();
};

