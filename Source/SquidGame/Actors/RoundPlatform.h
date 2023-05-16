// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoundPlatform.generated.h"

UCLASS()
class SQUIDGAME_API ARoundPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoundPlatform();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int32 FallingIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* RedMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnChangeMaterial();

};
