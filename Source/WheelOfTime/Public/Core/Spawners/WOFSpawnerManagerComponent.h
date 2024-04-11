// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WOFSpawnerManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WHEELOFTIME_API UWOFSpawnerManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWOFSpawnerManagerComponent();

	void SpawnEnemies();
	void InitSpawners();

private:
	TArray<TWeakObjectPtr<AActor>> Spawners;
};
