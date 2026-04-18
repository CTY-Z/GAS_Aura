// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	m_vigorDef.AttributeToCapture = UAuraAttributeSet::GetvigorAttribute();
	m_vigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	m_vigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(m_vigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* sourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* targetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters evaluationParameters;
	evaluationParameters.SourceTags = sourceTags;
	evaluationParameters.TargetTags = targetTags;

	float vigor = 0.f;
	GetCapturedAttributeMagnitude(m_vigorDef, Spec, evaluationParameters, vigor);
	vigor = FMath::Max<float>(vigor, 0.f);

	ICombatInterface* combatInterface =  Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 playerLevel = combatInterface->GetPlayerLevel();

	return 80.f + 2.5f * vigor + 10.f * playerLevel;
}
