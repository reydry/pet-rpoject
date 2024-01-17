// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "WheelOfTimePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class AWheelOfTimePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AWheelOfTimePlayerController();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	void MoveInput(const FInputActionValue& InputActionValue);
	void LookInput();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Movement;
};
