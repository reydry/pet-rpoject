// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/GameMode/WOFGameMode.h"

AWOFGameMode::AWOFGameMode()
{
	SpawnerManagerComponent = CreateDefaultSubobject<UWOFSpawnerManagerComponent>(TEXT("SpawnerManager"));
}

void AWOFGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnerManagerComponent->InitSpawners();
}