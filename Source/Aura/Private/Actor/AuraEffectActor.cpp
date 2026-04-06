// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* targetActor, TSubclassOf<UGameplayEffect> gameplayEffectClass)
{
	UAbilitySystemComponent* targetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetActor);
	if (targetAsc == nullptr) return;

	check(gameplayEffectClass);
	FGameplayEffectContextHandle effectContextHandle = targetAsc->MakeEffectContext();
	effectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle effectSpecHandle = targetAsc->MakeOutgoingSpec(gameplayEffectClass, actorLevel, effectContextHandle);
	const FActiveGameplayEffectHandle activeEffectHandle = targetAsc->ApplyGameplayEffectSpecToSelf(*effectSpecHandle.Data.Get());

	const bool bIsInfinite = effectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && (infiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap))
		map_activeEffectHandle_asc.Add(activeEffectHandle, targetAsc);
}

void AAuraEffectActor::OnOverlap(AActor* targetActor)
{
	if (instantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		ApplyEffectToTarget(targetActor, instantGameplayEffectClass);

	if (durationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		ApplyEffectToTarget(targetActor, durationGameplayEffectClass);

	if (infiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		ApplyEffectToTarget(targetActor, infiniteGameplayEffectClass);
}

void AAuraEffectActor::OnEndOverlap(AActor* targetActor)
{
	if (instantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		ApplyEffectToTarget(targetActor, instantGameplayEffectClass);

	if (durationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		ApplyEffectToTarget(targetActor, durationGameplayEffectClass);

	if (infiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		ApplyEffectToTarget(targetActor, infiniteGameplayEffectClass);

	if (infiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		auto targetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetActor);
		if (!IsValid(targetAsc)) return;
		
		TArray<FActiveGameplayEffectHandle> arr_handleToRemove;
		for (auto handlePair : map_activeEffectHandle_asc)
		{
			if (targetAsc == handlePair.Value)
			{
				targetAsc->RemoveActiveGameplayEffect(handlePair.Key, 1);
				arr_handleToRemove.Add(handlePair.Key);
			}
		}

		for (auto& handle : arr_handleToRemove)
			map_activeEffectHandle_asc.FindAndRemoveChecked(handle);
	}
}


