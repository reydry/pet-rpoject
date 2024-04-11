// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/PlayerState/WOFPlayerState.h"

#include "Abilities/WOFAttributeSet.h"

#include "AbilitySystemComponent.h"

AWOFPlayerState::AWOFPlayerState(const FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UWOFAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AWOFPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWOFPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void AWOFPlayerState::SetupAbilitySystem()
{
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();

	if (IsValid(AbilitySystem))
	{
		AbilitySystem->AddAttributeSetSubobject(AttributeSet.Get());
	}
}

UWOFAttributeSet* AWOFPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
