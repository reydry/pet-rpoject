// Copyright Epic Games, Inc. All Rights Reserved.

#include "WheelOfTimePlayerController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/KismetMathLibrary.h"

AWheelOfTimePlayerController::AWheelOfTimePlayerController()
{
	bShowMouseCursor = true;
}

void AWheelOfTimePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	LookInput();
}

void AWheelOfTimePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AWheelOfTimePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(Movement, ETriggerEvent::Triggered, this, &ThisClass::MoveInput);
	}
}

void AWheelOfTimePlayerController::MoveInput(const FInputActionValue& InputActionValue)
{
	APawn* MyPawn = GetPawn<APawn>();

	if (!IsValid(MyPawn))
	{
		return;
	}

	const FVector2D Value = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	if (Value.X != 0.0f)
	{
		const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
		MyPawn->AddMovementInput(MovementDirection, Value.X);
	}

	if (Value.Y != 0.0f)
	{
		const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		MyPawn->AddMovementInput(MovementDirection, Value.Y);
	}
}

void AWheelOfTimePlayerController::LookInput()
{
	FHitResult Hit;
	FRotator CursorRotation(FRotator::ZeroRotator);
	APawn* MyPawn = Cast<APawn>(GetPawn());

	if (MyPawn)
	{
		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1,
			false, Hit);

		CursorRotation.Yaw = UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), Hit.ImpactPoint).Yaw;
		MyPawn->SetActorRotation(CursorRotation);
	}
}

