// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyablePlatform.generated.h"

UCLASS()
class SQUIDGAME_API ADestroyablePlatform : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ADestroyablePlatform();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int32 RandomIndex = 0;
	
	UPROPERTY(Transient)
	float TimeToChangeColor = 0;

	UPROPERTY(Transient)
	FTimerHandle Delay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* RedMaterial;

	UPROPERTY(Transient)
	class ATimeManager* TimeManager;

	UPROPERTY(Transient)
	AActor* Actor;

	UPROPERTY(Transient, EditAnyWhere)
	class USoundCue* FallCue;

	TMap<int32, TFunction<void()>> RangeFunctionMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetNumberPlatform();
	virtual void ChangeNumberPlatform();
	virtual void ChangeStatePlatform();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeIndexPlatform();

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeLowZone();

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeMediumZone();

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeHighZone();

	
};
