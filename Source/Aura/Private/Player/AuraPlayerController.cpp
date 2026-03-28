// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/Highlight.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float deltaTime)
{
	Super::PlayerTick(deltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(m_auraContext);

	UEnhancedInputLocalPlayerSubsystem* subsystem
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(subsystem);
	
	subsystem->AddMappingContext(m_auraContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhanceInputComponent 
		= CastChecked<UEnhancedInputComponent>(InputComponent);

	enhanceInputComponent->BindAction(m_action_move, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& inputActionValue)
{
	const FVector2D inputAxisVector = inputActionValue.Get<FVector2D>();

	const FRotator rotation = GetControlRotation();
	const FRotator yawRotation(0.f, rotation.Yaw, 0.f);
	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* controlledPawn = GetPawn<APawn>())
	{
		controlledPawn->AddMovementInput(forwardDirection, inputAxisVector.Y);
		controlledPawn->AddMovementInput(rightDirection, inputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult cursorHit;

	GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);

	if (!cursorHit.bBlockingHit) return;

	lastActor = curActor;
	curActor = Cast<IHighlight>(cursorHit.GetActor());

	if (lastActor == nullptr)
	{
		if (curActor != nullptr)
			curActor->HighlightActor();
		else { }
	}
	else
	{
		if (curActor == nullptr)
			lastActor->UnHighlightActor();
		else
		{
			if (lastActor != curActor)
			{
				lastActor->UnHighlightActor();
				curActor->HighlightActor();
			}
			else { }
		}
	}
}
