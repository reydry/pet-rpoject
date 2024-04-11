// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WOFProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class WHEELOFTIME_API AWOFProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AWOFProjectile();

	UFUNCTION(BlueprintCallable)
	void FireInDirection(const FVector& Direction, const float& Speed);

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

};
