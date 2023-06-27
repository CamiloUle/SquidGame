// Fill out your copyright notice in the Description page of Project Settings.


#include "General/SquidGamePlayerController.h"
#include "Characters/SquidGameCharacter.h"
#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "Engine/GameEngine.h"
#include "Components/InputComponent.h"



ASquidGamePlayerController::ASquidGamePlayerController()
{
	 

}

void ASquidGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForwardPlayer1", this, &ASquidGamePlayerController::InputMovementXP1);
	InputComponent->BindAxis("MoveRightPlayer1", this, &ASquidGamePlayerController::InputMovementYP1);
	InputComponent->BindAction("JumpPlayer1", IE_Pressed, this, &ASquidGamePlayerController::InputJumpXP1);
	InputComponent->BindAction("JumpPlayer1", IE_Released, this, &ASquidGamePlayerController::InputJumpXP1);
	InputComponent->BindAction("StunPlayer1", IE_Pressed, this, &ASquidGamePlayerController::SetStunStatePlayer1);
	InputComponent->BindAction("StunPlayer1", IE_Released, this, &ASquidGamePlayerController::SetStunStatePlayer1);


	InputComponent->BindAxis("MoveForwardPlayer2", this, &ASquidGamePlayerController::InputMovementXP2);
	InputComponent->BindAxis("MoveRightPlayer2", this, &ASquidGamePlayerController::InputMovementYP2);
	InputComponent->BindAction("JumpPlayer2", IE_Pressed, this, &ASquidGamePlayerController::InputJumpXP2);
	InputComponent->BindAction("JumpPlayer2", IE_Released, this, &ASquidGamePlayerController::InputJumpXP2);
	InputComponent->BindAction("StunPlayer2", IE_Pressed, this, &ASquidGamePlayerController::SetStunStatePlayer2);
	InputComponent->BindAction("StunPlayer2", IE_Released, this, &ASquidGamePlayerController::SetStunStatePlayer2);
}

void ASquidGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor* > FoundActors;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASquidGameCharacter::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASquidGameCharacter* TempCharacter = Cast<ASquidGameCharacter>(Actor);

		if (TempCharacter) 
		{
			if (TempCharacter->CharacterIndex == 0) 
			{
				CharacterLeftPosition = TempCharacter;
			}
			else if (TempCharacter->CharacterIndex == 1)
			{
				CharacterRightPosition = TempCharacter;
			}
		}
	}
}

void ASquidGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	
}

void ASquidGamePlayerController::InputMovementXP1(float Value)
{
	if (CharacterLeftPosition)
	{
		CharacterLeftPosition->InputMovement.X = Value;
	}
}

void ASquidGamePlayerController::InputMovementYP1(float Value)
{
	if (CharacterLeftPosition)
	{
		CharacterLeftPosition->InputMovement.Y = Value;
	}
}

void ASquidGamePlayerController::InputMovementXP2(float Value)
{
	if (CharacterRightPosition) 
	{
		CharacterRightPosition->InputMovement.X = Value;
	}
}

void ASquidGamePlayerController::InputMovementYP2(float Value)
{
	if (CharacterRightPosition) 
	{
		CharacterRightPosition->InputMovement.Y = Value;
	}
}

void ASquidGamePlayerController::InputJumpXP1()
{
	if (CharacterLeftPosition)
	{
		CharacterLeftPosition->Jump();
		CharacterLeftPosition->bIsJumping = true;
	}
}

void ASquidGamePlayerController::InputJumpXP2()
{
	if (CharacterRightPosition)
	{
		CharacterRightPosition->Jump();
		CharacterRightPosition->bIsJumping = true;
	}
}

void ASquidGamePlayerController::SetStunStatePlayer1()
{
	if (CharacterLeftPosition) 
	{
		if (CharacterLeftPosition->StunCooldown > 0)
			return;

		 const float DistanceSqr = (CharacterLeftPosition->GetActorLocation() - CharacterRightPosition->GetActorLocation()).SizeSquared2D();

		 if (DistanceSqr <= (CharacterLeftPosition->StunRange * CharacterLeftPosition->StunRange)) 
		 {
			 CharacterRightPosition->bIsCharacterAplyStun = true;
			 CharacterRightPosition->OnSpawnSound();

			 CharacterLeftPosition->StunCooldown = CharacterLeftPosition->SetStunCooldown;
		 }
	}
}

void ASquidGamePlayerController::SetStunStatePlayer2()
{
	if (CharacterLeftPosition && CharacterRightPosition)
	{
		if (CharacterRightPosition->StunCooldown > 0)
			return;

		const float DistanceSqr = (CharacterLeftPosition->GetActorLocation() - CharacterRightPosition->GetActorLocation()).SizeSquared2D();

		if (DistanceSqr <= (CharacterRightPosition->StunRange * CharacterRightPosition->StunRange))
		{
			CharacterLeftPosition->bIsCharacterAplyStun = true;
			CharacterLeftPosition->OnSpawnSound();

			CharacterRightPosition->StunCooldown = CharacterRightPosition->SetStunCooldown;
		}
	}
}