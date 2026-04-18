// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMCharacterBase.h"

#include "AbilitySystemComponent.h"

ACMCharacterBase::ACMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ACMCharacterBase::GetAbilitySystemComponent() const
{
	return asc;
}

void ACMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACMCharacterBase::InitAbilityActorInfo()
{

}

void ACMCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> gameplayEffectClass, float level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(gameplayEffectClass);

	auto contextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const auto specHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(gameplayEffectClass, level, contextHandle);

	contextHandle.AddSourceObject(this);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*specHandle.Data.Get(), GetAbilitySystemComponent());
}

void ACMCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(defaultPrimaryAttributes);
	ApplyEffectToSelf(defaultSecondaryAttributes);
	ApplyEffectToSelf(defaultVitalAttributes);
}
