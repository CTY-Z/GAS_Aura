// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	const FAuraGameplayTags& gameplayTag = FAuraGameplayTags::Get();
	//gameplayTag.Attributes_Secondary_Armor.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, 
		FString(TEXT("-" + gameplayTag.Attributes_Secondary_Armor.ToString())));
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& arr_startupAbility)
{
	for (const auto abilityClass : arr_startupAbility)
	{
		auto spec = FGameplayAbilitySpec(abilityClass, 1);
		if (const UAuraGameplayAbility* auraAbility = Cast<UAuraGameplayAbility>(spec.Ability))
		{
			spec.DynamicAbilityTags.AddTag(auraAbility->startupInputTag);
			GiveAbility(spec);
		} 

	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& inputTag)
{
	if (!inputTag.IsValid()) return;

	for (auto& spec : GetActivatableAbilities())
	{
		AbilitySpecInputPressed(spec);
		if (spec.DynamicAbilityTags.HasTagExact(inputTag))
		{
			if (!spec.IsActive())
				TryActivateAbility(spec.Handle);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& inputTag)
{
	if (!inputTag.IsValid()) return;

	for (auto& spec : GetActivatableAbilities())
		AbilitySpecInputReleased(spec);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* asc, const FGameplayEffectSpec& spec, FActiveGameplayEffectHandle handle)
{
	FGameplayTagContainer tagContainer;
	spec.GetAllAssetTags(tagContainer);

	effectAssetTags.Broadcast(tagContainer);
}
