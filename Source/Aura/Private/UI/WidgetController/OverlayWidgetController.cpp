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
		.AddLambda([this](const FOnAttributeChangeData& data)
			{
				OnHealthChanged.Broadcast(data.NewValue);
			});
	asc->GetGameplayAttributeValueChangeDelegate(auraAttributeSet->GetmaxHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& data)
			{
				OnMaxHealthChanged.Broadcast(data.NewValue);
			});

	asc->GetGameplayAttributeValueChangeDelegate(auraAttributeSet->GetmanaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& data)
			{
				OnManaChanged.Broadcast(data.NewValue);
			});
	asc->GetGameplayAttributeValueChangeDelegate(auraAttributeSet->GetmaxManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& data)
			{
				OnMaxManaChanged.Broadcast(data.NewValue);
			});

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
