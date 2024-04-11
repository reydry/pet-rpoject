// Copyright Epic Games, Inc. All Rights Reserved.

#include "WheelOfTimeCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/Components/WOFHealthWidgetComponent.h"
#include "Core/PlayerState/WOFPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Abilities/WOFAttributeSet.h"

AWheelOfTimeCharacter::AWheelOfTimeCharacter()
{
	if (IsValid(GetCapsuleComponent()))
	{
		GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	}

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	if (IsValid(GetCharacterMovement()))
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
		GetCharacterMovement()->bConstrainToPlane = true;
		GetCharacterMovement()->bSnapToPlaneAtStart = true;
	}

	if (!IsValid(CameraBoom))
	{
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->SetUsingAbsoluteRotation(true);
		CameraBoom->TargetArmLength = 800.f;
		CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
		CameraBoom->bDoCollisionTest = false;
	}

	if (!IsValid(TopDownCameraComponent))
	{
		TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
		TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
		TopDownCameraComponent->bUsePawnControlRotation = false;
	}

	if (!IsValid(HealthWidgetComponent))
	{
		HealthWidgetComponent = CreateDefaultSubobject<UWOFHealthWidgetComponent>(TEXT("HealthWidgetComponent"));
		HealthWidgetComponent->SetupAttachment(GetMesh());
	}

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

UCameraComponent* AWheelOfTimeCharacter::GetTopDownCameraComponent() const
{
	return TopDownCameraComponent;
}

USpringArmComponent* AWheelOfTimeCharacter::GetCameraBoom() const
{
	return CameraBoom;
}

UAbilitySystemComponent* AWheelOfTimeCharacter::GetAbilitySystemComponent() const
{
	const AWOFPlayerState* OwningPlayerState = GetPlayerState<AWOFPlayerState>();

	if (!IsValid(OwningPlayerState))
	{
		return nullptr;
	}

	return OwningPlayerState->GetAbilitySystemComponent();
}

UWOFAttributeSet* AWheelOfTimeCharacter::GetAttributeSet() const
{
	const AWOFPlayerState* OwningPlayerState = GetPlayerState<AWOFPlayerState>();

	if (!IsValid(OwningPlayerState))
	{
		return nullptr;
	}

	return OwningPlayerState->GetAttributeSet();
}

void AWheelOfTimeCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilities();
	InitAttributes();
	SetupHealthBar();
	SubscribeToDelegates();
}

void AWheelOfTimeCharacter::SetupHealthBar()
{
	HealthWidgetComponent->InitComponentData(GetAbilitySystemComponent());
}

void AWheelOfTimeCharacter::InitAbilities()
{
	AWOFPlayerState* MyPlayerState = GetPlayerState<AWOFPlayerState>();
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();

	if (!IsValid(AbilitySystem) || !IsValid(MyPlayerState))
	{
		return;
	}

	MyPlayerState->SetupAbilitySystem();

	for (const TSubclassOf<UGameplayAbility> Ability : Abilities)
	{
		FGameplayAbilitySpecHandle AbilityHandle(AbilitySystem->GiveAbility(
			FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, INDEX_NONE, this))
		);

		GivenAbilities.Add(Ability, AbilityHandle);
	}

	AbilitySystem->InitAbilityActorInfo(this, this);
}

void AWheelOfTimeCharacter::InitAttributes()
{
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();

	if (!IsValid(AbilitySystem))
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystem->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);

	if (NewHandle.IsValid())
	{
		AbilitySystem->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
	}
}

void AWheelOfTimeCharacter::SubscribeToDelegates()
{
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();
	const UWOFAttributeSet* AttributeSet = GetAttributeSet();

	if (!IsValid(AbilitySystem) || !IsValid(AttributeSet))
	{
		return;
	}
	
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

void AWheelOfTimeCharacter::UnSubscribeFromDelegates()
{
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();
	const UWOFAttributeSet* AttributeSet = GetAttributeSet();

	if (!IsValid(AbilitySystem) || !IsValid(AttributeSet))
	{
		return;
	}

	AbilitySystem->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).RemoveAll(this);
}

void AWheelOfTimeCharacter::OnHealthChanged(const FOnAttributeChangeData& InData)
{
	if (InData.NewValue <= 0.0)
	{
		UnSubscribeFromDelegates();
		Destroy();
	}
}
