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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartHealthInitDelegateSignature);

UCLASS(Blueprintable)
class AWheelOfTimeCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWheelOfTimeCharacter();

	virtual void Tick(float DeltaSeconds) override;

	UCameraComponent* GetTopDownCameraComponent() const;

	USpringArmComponent* GetCameraBoom() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnStartHealthInitDelegateSignature OnStartHealthInitDelegate;

protected:
	void SetupHealthBar();

	void InitAbilities();

private:
	void InitAbilityAttributes();
	void SetWidgetComponentRotation();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWOFHealthWidgetComponent> HealthWidgetComponent;
};

