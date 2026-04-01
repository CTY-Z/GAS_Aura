// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const auto auraAttributeSet = CastChecked<UAuraAttributeSet>(attributeSet);

	OnHealthChanged.Broadcast(auraAttributeSet->Gethealth());
	OnMaxHealthChanged.Broadcast(auraAttributeSet->GetmaxHealth());

	OnManaChanged.Broadcast(auraAttributeSet->Getmana());
	OnMaxManaChanged.Broadcast(auraAttributeSet->GetmaxMana());
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	const auto auraAttributeSet = CastChecked<UAuraAttributeSet>(attributeSet);

	asc->GetGameplayAttributeValueChangeDelegate(auraAttributeSet->GethealthAttribute())
		.AddUObject(this, &UOverlayWidgetController::HealthChanged);
	asc->GetGameplayAttributeValueChangeDelegate(auraAttributeSet->GetmaxHealthAttribute())
		.AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	asc->GetGameplayAttributeValueChangeDelegate(auraAttributeSet->GetmanaAttribute())
		.AddUObject(this, &UOverlayWidgetController::ManaChanged);
	asc->GetGameplayAttributeValueChangeDelegate(auraAttributeSet->GetmaxManaAttribute())
		.AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& data) const
{
	OnHealthChanged.Broadcast(data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& data) const
{
	OnMaxHealthChanged.Broadcast(data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& data) const
{
	OnManaChanged.Broadcast(data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& data) const
{
	OnMaxManaChanged.Broadcast(data.NewValue);

}
