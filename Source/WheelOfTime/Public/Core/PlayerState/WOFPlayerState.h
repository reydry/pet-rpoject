// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Abilities/WOFAttributeSet.h"
#include "WOFPlayerState.generated.h"

class UWOFAttributeSet;

UCLASS()
class WHEELOFTIME_API AWOFPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWOFPlayerState(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void SetupAbilitySystem();

	UFUNCTION(BlueprintPure)
	UWOFAttributeSet* GetAttributeSet() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UWOFAttributeSet> AttributeSet;
};
