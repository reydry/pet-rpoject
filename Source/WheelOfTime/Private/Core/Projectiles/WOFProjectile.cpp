// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Projectiles/WOFProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AWOFProjectile::AWOFProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!IsValid(SphereCollision))
	{
		SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
		RootComponent = SphereCollision;
	}

	if (!IsValid(ProjectileMovementComponent))
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
		ProjectileMovementComponent->SetUpdatedComponent(SphereCollision);
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
}

void AWOFProjectile::FireInDirection(const FVector& Direction, const float& Speed)
{
	ProjectileMovementComponent->Velocity = Direction * Speed;
}
