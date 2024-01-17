// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "Abilities/WOFAttributeSet.h"
#include "WOFEnemy.generated.h"

class UAbilitySystemComponent;

UCLASS()
class WHEELOFTIME_API AWOFEnemy : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWOFEnemy();

	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupAbilitySystem();
	void SetupHealthBar();

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY()
	const UWOFAttributeSet* AttributeSet;

	UFUNCTION()
	void OnDeath();

	void SubscribeToDelegates();
	void UnSubscribeFromDelegates();
};
