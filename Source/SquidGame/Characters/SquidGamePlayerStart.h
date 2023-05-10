// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "SquidGamePlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class SQUIDGAME_API ASquidGamePlayerStart : public APlayerStart
{
	GENERATED_BODY()
	
public:

	

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	int32 Team;

};
