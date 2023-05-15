// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPost.generated.h"

UCLASS()
class SQUIDGAME_API ARotatingPost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingPost();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Transient)
	class AActorLight* ActorLight;

	UPROPERTY(EditAnywhere, Category = Movement)
	float AngleAxis;

	UPROPERTY(EditAnywhere, Category = Movement)
	FVector Dimensions;

	UPROPERTY(EditAnywhere, Category = Movement)
	FVector AxisVector;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Multiplier;
	
	UPROPERTY(EditInstanceOnly, Category = "Movement")
	bool bIsRotateOtherActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Rotated();

	void RotateAroundOtherActor();
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
