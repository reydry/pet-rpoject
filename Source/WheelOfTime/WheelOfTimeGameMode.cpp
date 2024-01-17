// Copyright Epic Games, Inc. All Rights Reserved.

#include "WheelOfTimeGameMode.h"
#include "UObject/ConstructorHelpers.h"

AWheelOfTimeGameMode::AWheelOfTimeGameMode()
{
	SpawnerManager = CreateDefaultSubobject<UWOFSpawnerManagerComponent>(TEXT("SpawnerManager"));
}

void AWheelOfTimeGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnerManager->InitSpawners();
}
