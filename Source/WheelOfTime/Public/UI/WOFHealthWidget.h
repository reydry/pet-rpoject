// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WOFHealthWidget.generated.h"

UCLASS()
class WHEELOFTIME_API UWOFHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void UpdateHealth(const float& InHealth);
	void UpdateHealth_Implementation(const float& Health);
};
