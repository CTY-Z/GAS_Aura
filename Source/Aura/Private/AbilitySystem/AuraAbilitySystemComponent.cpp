// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* asc, const FGameplayEffectSpec& spec, FActiveGameplayEffectHandle handle)
{
	GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue, FString("Effect Applied!"));

	FGameplayTagContainer tagContainer;
	spec.GetAllAssetTags(tagContainer);

	for (const FGameplayTag& tag : tagContainer)
	{
		const FString msg = FString::Printf(TEXT("GE Tag: %s"), *tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, msg);
	}
}
