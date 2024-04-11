// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Projectiles/WOFBladeFuryProjectile.h"

#include "Kismet/KismetMathLibrary.h"

void AWOFBladeFuryProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateLocation(DeltaSeconds);
}

void AWOFBladeFuryProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AWOFBladeFuryProjectile::UpdateLocation(float& InDeltaSeconds)
{
	if (!IsValid(Owner))
	{
		return;
	}

	Angle += RotationSpeed * InDeltaSeconds;

	const FVector OwnerLocation = Owner->GetActorLocation();
	FVector Location = UKismetMathLibrary::RotateAngleAxis(FVector(Radius, 0, 0), Angle, FVector(0.0f, 0.0f, 1.0f));

	Location += OwnerLocation;

	SetActorLocation(Location);
}
