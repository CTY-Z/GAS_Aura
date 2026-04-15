// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMEnemy.h"
#include "Aura/Aura.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"

ACMEnemy::ACMEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	asc = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	asc->SetIsReplicated(true);
	asc->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	attributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}

void ACMEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();
}

void ACMEnemy::InitAbilityActorInfo()
{
	asc->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(asc)->AbilityActorInfoSet();
}

void ACMEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	weapon->SetRenderCustomDepth(true);
	weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ACMEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	weapon->SetRenderCustomDepth(false);
}

int32 ACMEnemy::GetPlayerLevel()
{
	return level;
}


