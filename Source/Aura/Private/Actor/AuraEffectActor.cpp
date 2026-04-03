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
	auto targetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetActor);
	if (targetAsc == nullptr) return;

	check(gameplayEffectClass);
	FGameplayEffectContextHandle effectContextHandle = targetAsc->MakeEffectContext();
	effectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle effectSpecHandle = targetAsc->MakeOutgoingSpec(gameplayEffectClass, 1.f, effectContextHandle);
	targetAsc->ApplyGameplayEffectSpecToSelf(*effectSpecHandle.Data.Get());
}


