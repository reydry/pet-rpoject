// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameplayEffectTypes.h"
#include "WOFHealthWidgetComponent.generated.h"

class UAbilitySystemComponent;

UCLASS()
class WHEELOFTIME_API UWOFHealthWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	void InitComponentData(UAbilitySystemComponent* InAbilitySystemComponent);
	void UpdateHealth(const float& InHealth) const;
	void OnHealthChanged(const FOnAttributeChangeData& InData) const;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void UpdateWidgetRotation();

private:
	TWeakObjectPtr<APlayerCameraManager> PlayerCameraManager;
};
