// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "UI/HUD/AuraHUD.h"
#include "Player/AuraPlayerState.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* worldContextObject)
{
	if (APlayerController* playerCtrl = UGameplayStatics::GetPlayerController(worldContextObject, 0))
	{
		if (AAuraHUD* hud = Cast<AAuraHUD>(playerCtrl->GetHUD()))
		{
			AAuraPlayerState* playerState = playerCtrl->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* asc = playerState->GetAbilitySystemComponent();
			UAttributeSet* attributeSet = playerState->GetAttributeSet();

			return hud->GetOverlayWidgetController({playerCtrl, playerState, asc, attributeSet});
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* worldContextObject)
{
	if (APlayerController* playerCtrl = UGameplayStatics::GetPlayerController(worldContextObject, 0))
	{
		if (AAuraHUD* hud = Cast<AAuraHUD>(playerCtrl->GetHUD()))
		{
			AAuraPlayerState* playerState = playerCtrl->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* asc = playerState->GetAbilitySystemComponent();
			UAttributeSet* attributeSet = playerState->GetAttributeSet();

			return hud->GetAttributeMenuWidgetController({ playerCtrl, playerState, asc, attributeSet });
		}
	}

	return nullptr;
}