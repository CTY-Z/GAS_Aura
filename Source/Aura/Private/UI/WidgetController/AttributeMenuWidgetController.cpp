// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbackToDependencies()
{
	UAuraAttributeSet* as = CastChecked<UAuraAttributeSet>(attributeSet);
	check(attributeInfo);

	for (auto& pair : as->map_tag_attribute)
	{
		asc->GetGameplayAttributeValueChangeDelegate(pair.Value()).AddLambda(
			[this, pair](const FOnAttributeChangeData& data) 
			{
				BroadcastAttributeInfo(pair.Key, pair.Value());
			});
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* as = CastChecked<UAuraAttributeSet>(attributeSet);
	check(attributeInfo);

	for (auto& pair : as->map_tag_attribute)
		BroadcastAttributeInfo(pair.Key, pair.Value());
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& tag, const FGameplayAttribute& attribute) const
{
	FAuraAttributeInfo info = attributeInfo->FindAttributeInfoByTag(tag);
	info.attributeValue = attribute.GetNumericValue(attributeSet);
	attributeInfoDelegate.Broadcast(info);
}