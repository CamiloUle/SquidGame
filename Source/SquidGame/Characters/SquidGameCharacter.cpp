// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/SquidGameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actors/CharacterCameraActor.h"
#include "DrawDebugHelpers.h"
#include "Actors/ActorLight.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/YoungHeeActor.h"
#include "General/SquidGameGameState.h"

//////////////////////////////////////////////////////////////////////////
// ASquidGameCharacter

ASquidGameCharacter::ASquidGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	//GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

void ASquidGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	RandomCharacterID = FMath::RandRange(1, 500);
}


void ASquidGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsCharacterDead || bIscharacterOverlapGoal)
	{
		RemovePlayerInput();
	}

	MovementDirection = FVector(InputMovement.X, InputMovement.Y, InputMovement.Z);
	AddMovementInput(MovementDirection);
	if (MovementDirection.Size2D() > 0)
	{
		LastMovementDirection = MovementDirection;
	}
}

void ASquidGameCharacter::RemovePlayerInput()
{
	bIsJumping = false;
	InputMovement.X = 0;
	InputMovement.Y = 0;
}
void ASquidGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}
