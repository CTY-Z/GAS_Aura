// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CMCharacterBase.h"
#include "Interaction/Highlight.h"
#include "CMEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ACMEnemy : public ACMCharacterBase, public IHighlight
{
	GENERATED_BODY()
	
public:
	ACMEnemy();

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
