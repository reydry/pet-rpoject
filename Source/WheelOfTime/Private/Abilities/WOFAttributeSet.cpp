// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/WOFAttributeSet.h"
#include "GameplayEffectExtension.h"

void UWOFAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Max(GetHealth(), 0.0f));

		if (FMath::IsNearlyZero(GetHealth()))
		{
			OnDeathDelegate.Broadcast();
		}
	}
}

