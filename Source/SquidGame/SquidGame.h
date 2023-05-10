// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#define print_unique(id, text) { if (GEngine) GEngine->AddOnScreenDebugMessage(id, 5.0, FColor::Yellow, text); }
