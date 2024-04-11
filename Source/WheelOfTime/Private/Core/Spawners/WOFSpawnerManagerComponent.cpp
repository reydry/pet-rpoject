// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Spawners/WOFSpawnerManagerComponent.h"

#include "Core/Spawners/WOFBaseSpawner.h"
#include "Kismet/GameplayStatics.h"

UWOFSpawnerManagerComponent::UWOFSpawnerManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWOFSpawnerManagerComponent::SpawnEnemies()
{
	if(Spawners.IsEmpty())
	{
		return; 
	}

	for(TWeakObjectPtr<AActor> Spawner : Spawners)
	{

	}
}

void UWOFSpawnerManagerComponent::InitSpawners()
{
	TArray<AActor*> OutActors;
	
	UGameplayStatics::GetAllActorsOfClass(this, AWOFBaseSpawner::StaticClass(), OutActors);

	for (AActor* Actor : OutActors)
	{
		Spawners.AddUnique(Actor);
	}
}

