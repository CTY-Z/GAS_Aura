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

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes ")
	FGameplayAttributeData health;
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& oldHealth) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes ")
	FGameplayAttributeData maxHealth;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, maxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes ")
	FGameplayAttributeData mana;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& oldHealth) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes ")
	FGameplayAttributeData maxMana;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& oldMaxHealth) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, maxMana);
};
