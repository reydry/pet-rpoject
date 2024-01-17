// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Spawners/WOFBaseSpawner.h"

AWOFBaseSpawner::AWOFBaseSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWOFBaseSpawner::BeginPlay()
{
	Super::BeginPlay();
}
