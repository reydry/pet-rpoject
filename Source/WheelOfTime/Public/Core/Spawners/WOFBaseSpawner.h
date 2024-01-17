// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WOFBaseSpawner.generated.h"

UCLASS()
class WHEELOFTIME_API AWOFBaseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AWOFBaseSpawner();

protected:
	virtual void BeginPlay() override;

};
