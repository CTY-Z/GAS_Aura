// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	Inithealth(50.f);
	Initmana(10.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, health, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, armorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, criticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, criticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, criticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, maxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, healthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, maxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, manaRegeneration, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, vigor, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& attribute, float& newValue)
{
	Super::PreAttributeChange(attribute, newValue);

		//运算符重载
	if (attribute == GethealthAttribute())
		newValue = FMath::Clamp(newValue, 0, GetmaxHealth());
	if (attribute == GetmanaAttribute())
		newValue = FMath::Clamp(newValue, 0, GetmaxMana());
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties props;
	SetEffectProperties(Data, props);

	if (Data.EvaluatedData.Attribute == GethealthAttribute())
		Sethealth(FMath::Clamp(Gethealth(), 0.f, GetmaxHealth()));
	if (Data.EvaluatedData.Attribute == GetmanaAttribute())
		Setmana(FMath::Clamp(Getmana(), 0.f, GetmaxMana()));
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& data, FEffectProperties& props) const
{
	//Target是这个AttributeSet的owner

	props.effectContextHandle = data.EffectSpec.GetContext();
	props.sourceAsc = props.effectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(props.sourceAsc) && props.sourceAsc->AbilityActorInfo.IsValid() && props.sourceAsc->AbilityActorInfo->AvatarActor.IsValid())
	{
		props.sourceAvatarActor = props.sourceAsc->AbilityActorInfo->AvatarActor.Get();

		props.sourceController = props.sourceAsc->AbilityActorInfo->PlayerController.Get();
		if (props.sourceController == nullptr && props.sourceAvatarActor != nullptr)
		{
			if (const APawn* pawn = Cast<APawn>(props.sourceAvatarActor))
				props.sourceController = pawn->GetController();
		}

		if (props.sourceController)
			ACharacter* sourceCharacter = Cast<ACharacter>(props.sourceController->GetPawn());
	}

	if (data.Target.AbilityActorInfo.IsValid() && data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		props.targetAvatarActor = data.Target.AbilityActorInfo->AvatarActor.Get();
		props.targetController = data.Target.AbilityActorInfo->PlayerController.Get();
		props.targetCharacter = Cast<ACharacter>(props.targetAvatarActor);

		props.targetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(props.targetAvatarActor);
	}
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& oldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, health, oldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, maxHealth, oldMaxHealth);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& oldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, healthRegeneration, oldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& oldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, mana, oldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& oldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, maxMana, oldMaxMana);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& oldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, manaRegeneration, oldManaRegeneration);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& oldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, armor, oldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& oldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, armorPenetration, oldArmorPenetration);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& oldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, blockChance, oldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& oldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, criticalHitChance, oldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& oldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, criticalHitDamage, oldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& oldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, criticalHitResistance, oldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& oldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, strength, oldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& oldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, intelligence, oldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& oldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, resilience, oldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& oldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, vigor, oldVigor);
}


