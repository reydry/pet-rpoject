// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/WOFAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "WOFHealthWidgetComponent.generated.h"

UCLASS()
class WHEELOFTIME_API UWOFHealthWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:

	void InitHealthInfo();
	void UpdateHealth(const float& InHealth) const;
	void OnHealthChanged(const FOnAttributeChangeData& InData) const;

};
