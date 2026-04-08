// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

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

	Cast<UAuraAbilitySystemComponent>(asc)->effectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& assetTags) 
		{
			for (const FGameplayTag& tag : assetTags)
			{
				auto tag_Msg = FGameplayTag::RequestGameplayTag(FName("Msg"));
				if (tag.MatchesTag(tag_Msg))
				{
					const FUIWidgetRow* row = GetDataTableRowByTag<FUIWidgetRow>(msgWidgetDataTable, tag);
					msgWidgetRowDelegate.Broadcast(*row);
				}

				//const FString msg = FString::Printf(TEXT("GE Tag: %s"), *tag.ToString());
				//GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, msg);

			}
		});
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
