// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() { }

	FGameplayEffectContextHandle effectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* sourceAsc = nullptr;

	UPROPERTY()
	AActor* sourceAvatarActor = nullptr;

	UPROPERTY()
	AController* sourceController = nullptr;

	UPROPERTY()
	ACharacter* sourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* targetAsc = nullptr;

	UPROPERTY()
	AActor* targetAvatarActor = nullptr;

	UPROPERTY()
	AController* targetController = nullptr;

	UPROPERTY()
	ACharacter* targetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	//TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy > ::FFuncPtr
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> map_tag_attribute;

#pragma region Primary

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes ")
	FGameplayAttributeData strength;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& oldStrength) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes ")
	FGameplayAttributeData intelligence;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& oldIntelligence) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes ")
	FGameplayAttributeData resilience;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& oldResilience) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes ")
	FGameplayAttributeData vigor;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& oldVigor) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, vigor);

#pragma endregion

#pragma region Secondary

	//MaxHealth
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes ")
	FGameplayAttributeData maxHealth;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, maxHealth);

	//HealthRegeneration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Vital Attributes ")
	FGameplayAttributeData healthRegeneration;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& oldHealthRegeneration) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, healthRegeneration);

	//MaxMana
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes ")
	FGameplayAttributeData maxMana;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& oldMaxHealth) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, maxMana);

	//ManaRegeneration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Vital Attributes ")
	FGameplayAttributeData manaRegeneration;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& oldManaRegeneration) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, manaRegeneration);

	//Armor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Vital Attributes ")
	FGameplayAttributeData armor;
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& oldArmor) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, armor);

	//ArmorPenetration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Vital Attributes ")
	FGameplayAttributeData armorPenetration;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& oldArmorPenetration) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, armorPenetration);

	//BlockChance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Vital Attributes ")
	FGameplayAttributeData blockChance;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& oldBlockChance) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, blockChance);

	//CriticalHitChance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Vital Attributes ")
	FGameplayAttributeData criticalHitChance;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& oldCriticalHitChance) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, criticalHitChance);

	//CriticalHitDamage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Vital Attributes ")
	FGameplayAttributeData criticalHitDamage;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& oldCriticalHitDamage) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, criticalHitDamage);

	//CriticalHitResistance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Vital Attributes ")
	FGameplayAttributeData criticalHitResistance;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& oldCriticalHitResistance) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, criticalHitResistance);

#pragma endregion

#pragma region Vital

	//Health
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes ")
	FGameplayAttributeData health;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& oldHealth) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, health);

	//Mana
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes ")
	FGameplayAttributeData mana;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& oldHealth) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, mana);

#pragma endregion

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& data, FEffectProperties& props) const;
};
