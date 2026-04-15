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

	virtual int32 GetPlayerLevel() override;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 level = 1;

private:

};
