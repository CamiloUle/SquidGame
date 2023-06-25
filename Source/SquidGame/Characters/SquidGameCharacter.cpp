// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/SquidGameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "DrawDebugHelpers.h"
#include "Actors/ActorLight.h"
#include "Actors/YoungHeeActor.h"
#include "Actors/Bucket.h"
#include "Actors/EvilPopcorn.h"
#include "Actors/CharacterCameraActor.h"

#include "General/SquidGameGameState.h"

#include "Actors/Popcorn.h"
#include "Engine/SkeletalMesh.h"

#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

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

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bucket"));
	StaticMesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(StaticMesh);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASquidGameCharacter::OnOverlapBegin);
}



void ASquidGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	RandomCharacterID = FMath::RandRange(1, 500);

	if (bIsSetBucket) 
	{
		StaticMesh->SetVisibility(true);
	}
	else if (!bIsSetBucket) 
	{
		StaticMesh->SetVisibility(false);
	}
}


void ASquidGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StunCooldown -= DeltaTime;

	if (bIsCharacterDead || bIscharacterOverlapGoal)
	{
		RemovePlayerInput();
	}

	if (bIsCharacterAplyStun) 
	{
		RemovePlayerInput();
		TimeToStun -= DeltaTime;

		if (TimeToStun <= 0) 
		{
			bIsCharacterAplyStun = false;
			TimeToStun = SetTimeToStun;
		}
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

void ASquidGameCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		EvilPopcorn = Cast<AEvilPopcorn>(OtherActor);
		Popcorn = Cast<APopcorn>(OtherActor);

		if (Popcorn != nullptr)
		{
			NumOfHits += 1;
			Popcorn->Destroy();

			FString ValueString = FString::Printf(TEXT("Num of Hits: %d"), NumOfHits);

			FVector2D ScreenPosition(100.0f, 100.0f); // Posición en la pantalla donde se mostrará el mensaje
			float DisplayTime = 5.0f; // Tiempo en segundos durante el cual se mostrará el mensaje

			FColor TextColor = FColor::Red;
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, DisplayTime, TextColor, ValueString, false);
			}

		}
		else if (EvilPopcorn != nullptr)
		{
			NumOfHits -= 1;
			EvilPopcorn->Destroy();
		}
	}
}

void ASquidGameCharacter::PlayStunSound()
{
	USoundCue* SoundCue = LoadObject<USoundCue>(nullptr, TEXT("/Game/Content/Media/Sounds/Uh.SoundCue"));

	if (SoundCue)
	{
		FVector SoundLocation = GetActorLocation(); 

		UGameplayStatics::PlaySoundAtLocation(this, SoundCue, SoundLocation);
	}
}
