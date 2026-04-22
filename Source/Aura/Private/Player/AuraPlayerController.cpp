// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include <AbilitySystemBlueprintLibrary.h>

#include "EnhancedInputSubsystems.h"
#include "Interaction/Highlight.h"
#include "GameplayTagContainer.h"
#include "Input/AuraInputComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

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
	
	if (subsystem)
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

	UAuraInputComponent* auraInputComponent 
		= CastChecked<UAuraInputComponent>(InputComponent);

	auraInputComponent->BindAction(m_action_move, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

	auraInputComponent->BindAbilityAction(m_inputConfig, this,
		&ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag inputTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *inputTag.ToString());
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag inputTag)
{
	//GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, *inputTag.ToString());

	if (GetAsc() == nullptr) return;
	GetAsc()->AbilityInputTagReleased(inputTag);
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag inputTag)
{
	//GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Green, *inputTag.ToString());

	if (GetAsc() == nullptr) return;
	GetAsc()->AbilityInputTagHeld(inputTag);
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

UAuraAbilitySystemComponent* AAuraPlayerController::GetAsc()
{
	if (m_auraAsc == nullptr)
		m_auraAsc = Cast<UAuraAbilitySystemComponent>
			(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));

	return m_auraAsc;
}
