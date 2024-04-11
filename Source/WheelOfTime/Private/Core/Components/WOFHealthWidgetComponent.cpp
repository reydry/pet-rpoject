// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Components/WOFHealthWidgetComponent.h"

#include "AbilitySystemComponent.h"
#include "Abilities/WOFAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/WOFHealthWidget.h"

void UWOFHealthWidgetComponent::InitComponentData(UAbilitySystemComponent* InAbilitySystemComponent)
{
	const UWOFAttributeSet* AttributeSet = InAbilitySystemComponent->GetSet<UWOFAttributeSet>();

	if (!IsValid(InAbilitySystemComponent) || !IsValid(AttributeSet))
	{
		return;
	}

	InitWidget();
	InAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
	UpdateHealth(AttributeSet->GetHealth());

	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
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

void UWOFHealthWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateWidgetRotation();
}

void UWOFHealthWidgetComponent::UpdateWidgetRotation()
{
	if (PlayerCameraManager.IsValid())
	{
		SetWorldRotation(
			UKismetMathLibrary::FindLookAtRotation(
				GetComponentLocation(),
				PlayerCameraManager->GetCameraLocation()
			)
		);
	}
}

