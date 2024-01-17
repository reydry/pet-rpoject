// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Components/WOFHealthWidgetComponent.h"

#include "AbilitySystemComponent.h"
#include "Abilities/WOFAttributeSet.h"
#include "UI/WOFHealthWidget.h"
#include "WheelOfTime/WheelOfTimeCharacter.h"

void UWOFHealthWidgetComponent::InitHealthInfo()
{
	const AWheelOfTimeCharacter* Character = Cast<AWheelOfTimeCharacter>(GetOwner());

	if (!IsValid(Character))
	{
		return;
	}

	UAbilitySystemComponent* AbilitySystem = Character->GetAbilitySystemComponent();
	const UWOFAttributeSet* AttributeSet = AbilitySystem->GetSet<UWOFAttributeSet>();

	if (!IsValid(AbilitySystem) || !IsValid(AttributeSet))
	{
		return;
	}

	InitWidget();
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
	UpdateHealth(AttributeSet->GetHealth());
}

void UWOFHealthWidgetComponent::UpdateHealth(const float& InHealth) const
{
	UWOFHealthWidget* HealthWidget = Cast<UWOFHealthWidget>(GetWidget());

	if (IsValid(HealthWidget))
	{
		HealthWidget->UpdateHealth(InHealth);
	}
}

void UWOFHealthWidgetComponent::OnHealthChanged(const FOnAttributeChangeData& InData) const
{
	UpdateHealth(InData.NewValue);
}

