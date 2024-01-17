// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "WOFAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegateSignature);

UCLASS()
class WHEELOFTIME_API UWOFAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, Health);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health); 
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, Level);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Level);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Level);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Level);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	FOnDeathDelegateSignature OnDeathDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Level;

private:
	

};
