// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	m_intelligenceDef.AttributeToCapture = UAuraAttributeSet::GetintelligenceAttribute();
	m_intelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	m_intelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(m_intelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* sourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* targetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters evaluationParameters;
	evaluationParameters.SourceTags = sourceTags;
	evaluationParameters.TargetTags = targetTags;

	float intelligence = 0.f;
	GetCapturedAttributeMagnitude(m_intelligenceDef, Spec, evaluationParameters, intelligence);
	intelligence = FMath::Max<float>(intelligence, 0.f);

	ICombatInterface* combatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 playerLevel = combatInterface->GetPlayerLevel();

	return 50.f + 2.5f * intelligence + 15.f * playerLevel;
}