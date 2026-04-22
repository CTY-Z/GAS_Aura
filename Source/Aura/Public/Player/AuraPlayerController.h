// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "AuraPlayerController.generated.h"

struct FInputActionValue;
struct FGameplayTag;
class UInputMappingContext;
class UInputAction;
class IHighlight;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();

	virtual void PlayerTick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> m_auraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> m_action_move;

	TObjectPtr<IHighlight> lastActor;
	TObjectPtr<IHighlight> curActor;


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> m_inputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraAbilitySystemComponent> m_auraAsc;

	void AbilityInputTagPressed(FGameplayTag inputTag);
	void AbilityInputTagReleased(FGameplayTag inputTag);
	void AbilityInputTagHeld(FGameplayTag inputTag);

	void Move(const FInputActionValue& inputActionValue);

	void CursorTrace();

	UAuraAbilitySystemComponent* GetAsc();

};
