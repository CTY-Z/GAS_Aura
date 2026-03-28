// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	asc = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	asc->SetIsReplicated(true);
	asc->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	attributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return asc;
}
