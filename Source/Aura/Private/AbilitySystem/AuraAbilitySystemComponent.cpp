// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	const FAuraGameplayTags& gameplayTag = FAuraGameplayTags::Get();
	//gameplayTag.Attributes_Secondary_Armor.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, 
		FString(TEXT("-" + gameplayTag.Attributes_Secondary_Armor.ToString())));
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* asc, const FGameplayEffectSpec& spec, FActiveGameplayEffectHandle handle)
{
	FGameplayTagContainer tagContainer;
	spec.GetAllAssetTags(tagContainer);

	effectAssetTags.Broadcast(tagContainer);
}
