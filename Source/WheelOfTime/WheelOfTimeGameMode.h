// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Spawners/WOFSpawnerManagerComponent.h"
#include "GameFramework/GameModeBase.h"
#include "WheelOfTimeGameMode.generated.h"

UCLASS(minimalapi)
class AWheelOfTimeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWheelOfTimeGameMode();

protected:
	void BeginPlay() override;

protected:
	UPROPERTY()
	UWOFSpawnerManagerComponent* SpawnerManager;
};

