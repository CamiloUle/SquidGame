// Fill out your copyright notice in the Description page of Project Settings.


#include "Bucket.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Actors/EvilPopcorn.h"
#include "Actors/Popcorn.h"
#include "Characters/SquidGameCharacter.h"
#include "General/SquidGamePlayerController.h"


// Sets default values
ABucket::ABucket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	//BoxComponent->SetupAttachment(RootComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABucket::OnOverlapBegin);
}

void ABucket::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this) 
	{
		EvilPopcorn = Cast<AEvilPopcorn>(OtherActor);
		Popcorn = Cast<APopcorn>(OtherActor);

		if (Popcorn != nullptr) 
		{
			NumOfHits += 1;

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
		}
	}
}

// Called when the game starts or when spawned
void ABucket::BeginPlay()
{
	Super::BeginPlay();

	FName SocketName = TEXT("headSocket");
	FName TagBucket1 = FName("Player1");
	FName TagBucket2 = FName("Player2");

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	/*if (PlayerCharacter && PlayerCharacter->GetMesh())
	{
		if (PlayerCharacter->Tags.Contains(TagBucket1))
		{
			AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);	
		}
		else if (PlayerCharacter->Tags.Contains(TagBucket1)) 
		{
			AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
		}
	}*/

	SetUpCharacter();
}
	


// Called every frame
void ABucket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SetNewPosition();
}

void ABucket::SetUpCharacter()
{
	FName TagBucket1 = FName("Player1");
	FName TagBucket2 = FName("Player2");
	TArray<AActor*>FoundCharacter;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASquidGameCharacter::StaticClass(), FoundCharacter);

	ASquidGameCharacter* TempCharacter = nullptr;

	for (auto Actor : FoundCharacter) 
	{
		TempCharacter = Cast<ASquidGameCharacter>(Actor);

		if (TempCharacter->ActorHasTag("Player1")) 
		{
			CharacterLeftPosition = TempCharacter;
		}
		else if (TempCharacter->ActorHasTag("Player2"))
		{
			CharacterRightPosition = TempCharacter;
		}
		
	}

	AttachBucketToCharacter(0);
}

void ABucket::AttachBucketToCharacter(int32 PlayerIndex)
{
	ASquidGameCharacter* CharacterToAttach = nullptr;

	if (PlayerIndex == 0)
	{
		CharacterToAttach = CharacterLeftPosition;
	}
	else if (PlayerIndex == 1)
	{
		CharacterToAttach = CharacterRightPosition;
	}

	if (CharacterToAttach)
	{
		FName SocketName = TEXT("headSocket");
		AttachToComponent(CharacterToAttach->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
	}
}



