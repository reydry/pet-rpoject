// Copyright Epic Games, Inc. All Rights Reserved.

#include "WheelOfTimeCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/Components/WOFHealthWidgetComponent.h"
#include "Core/PlayerState/WOFPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


AWheelOfTimeCharacter::AWheelOfTimeCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; 

	HealthWidgetComponent = CreateDefaultSubobject<UWOFHealthWidgetComponent>(TEXT("HealthWidgetComponent"));
	HealthWidgetComponent->SetupAttachment(GetMesh());

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AWheelOfTimeCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	SetWidgetComponentRotation();
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

void AWheelOfTimeCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityAttributes();
	SetupHealthBar();
	InitAbilities();
}

void AWheelOfTimeCharacter::SetupHealthBar()
{
	HealthWidgetComponent->InitHealthInfo();
}

void AWheelOfTimeCharacter::InitAbilities()
{
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();

	if (!IsValid(AbilitySystem))
	{
		return;
	}

	for (const TSubclassOf<UGameplayAbility> Ability : Abilities)
	{
		AbilitySpecHandles.Add(
			AbilitySystem->GiveAbility(
					FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, INDEX_NONE, this))
		);
	}
}

void AWheelOfTimeCharacter::InitAbilityAttributes()
{
	AWOFPlayerState* OwningPlayerState = GetPlayerState<AWOFPlayerState>();

	if (IsValid(OwningPlayerState))
	{
		OwningPlayerState->SetupAbilitySystem();
	}

	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();

	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
}

void AWheelOfTimeCharacter::SetWidgetComponentRotation()
{
	HealthWidgetComponent->SetWorldRotation(
		UKismetMathLibrary::FindLookAtRotation(
			HealthWidgetComponent->GetComponentLocation(),
			TopDownCameraComponent->GetComponentLocation()
		)
	);
}
