// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Spawners/WOFSpawnerManagerComponent.h"
#include "GameFramework/GameMode.h"
#include "WOFGameMode.generated.h"

UCLASS()
class WHEELOFTIME_API AWOFGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AWOFGameMode();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UWOFSpawnerManagerComponent* SpawnerManagerComponent;
};
