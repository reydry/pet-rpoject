// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "Abilities/WOFAttributeSet.h"
#include "WOFEnemy.generated.h"

class UAbilitySystemComponent;
class UWOFHealthWidgetComponent;

UCLASS()
class WHEELOFTIME_API AWOFEnemy : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	AWOFEnemy();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

	void SetupAbilitySystem();
	void SetupHealthBar();

private:
	UFUNCTION()
	void OnDeath();

	void SubscribeToDelegates();
	void UnSubscribeFromDelegates();

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWOFHealthWidgetComponent> HealthWidgetComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY()
	const UWOFAttributeSet* AttributeSet;
};
