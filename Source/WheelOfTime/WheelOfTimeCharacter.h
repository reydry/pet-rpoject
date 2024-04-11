// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameplayAbilitySpec.h"
#include "WheelOfTimeCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UGameplayAbility;
class UWOFHealthWidgetComponent;
class UWOFAttributeSet;
class UGameplayEffect;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartHealthInitDelegateSignature);

UCLASS(Blueprintable)
class AWheelOfTimeCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWheelOfTimeCharacter();

	UCameraComponent* GetTopDownCameraComponent() const;

	USpringArmComponent* GetCameraBoom() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UWOFAttributeSet* GetAttributeSet() const;

	virtual void PossessedBy(AController* NewController) override;

protected:
	void SetupHealthBar();

	void InitAbilities();

private:
	void InitAttributes();
	void SubscribeToDelegates();
	void UnSubscribeFromDelegates();
	void OnHealthChanged(const FOnAttributeChangeData& InData);

public:
	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnStartHealthInitDelegateSignature OnStartHealthInitDelegate;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWOFHealthWidgetComponent> HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<UGameplayAbility>, FGameplayAbilitySpecHandle> GivenAbilities;
};

