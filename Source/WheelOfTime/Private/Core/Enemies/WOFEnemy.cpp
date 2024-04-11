// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Enemies/WOFEnemy.h"
#include "AbilitySystemComponent.h"
#include "Core/Components/WOFHealthWidgetComponent.h"

AWOFEnemy::AWOFEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("ASC");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	SetRootComponent(StaticMeshComponent);

	if (!IsValid(HealthWidgetComponent))
	{
		HealthWidgetComponent = CreateDefaultSubobject<UWOFHealthWidgetComponent>("HealthWidgetComponent");
		HealthWidgetComponent->SetupAttachment(StaticMeshComponent);
	}
}

void AWOFEnemy::BeginPlay()
{
	Super::BeginPlay();

	SetupAbilitySystem();
	SetupHealthBar();
	SubscribeToDelegates();
}

UAbilitySystemComponent* AWOFEnemy::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

void AWOFEnemy::SetupAbilitySystem()
{
	if (!IsValid(AbilitySystem))
	{
		return;
	}

	AbilitySystem->InitAbilityActorInfo(this, this);
	AttributeSet = AbilitySystem->GetSet<UWOFAttributeSet>();
}

void AWOFEnemy::SetupHealthBar()
{
	HealthWidgetComponent->InitComponentData(AbilitySystem);
}

void AWOFEnemy::OnDeath()
{
	UnSubscribeFromDelegates();
	Destroy();
}

void AWOFEnemy::SubscribeToDelegates()
{
	if (!IsValid(AttributeSet))
	{
		return;
	}

	UWOFAttributeSet* WOFSet = const_cast<UWOFAttributeSet*>(AttributeSet);
	WOFSet->OnDeathDelegate.AddUniqueDynamic(this, &ThisClass::OnDeath);
}

void AWOFEnemy::UnSubscribeFromDelegates()
{
	if (!IsValid(AttributeSet))
	{
		return;
	}

	UWOFAttributeSet* WOFSet = const_cast<UWOFAttributeSet*>(AttributeSet);
	WOFSet->OnDeathDelegate.RemoveDynamic(this, &ThisClass::OnDeath);
}
