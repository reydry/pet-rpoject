// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Projectiles/WOFProjectile.h"
#include "WOFBladeFuryProjectile.generated.h"

UCLASS()
class WHEELOFTIME_API AWOFBladeFuryProjectile : public AWOFProjectile
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:
	void UpdateLocation(float& InDeltaSeconds);

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float RotationSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess))
	float Radius = 300.0f;

	float Angle = 0.0f;
};
