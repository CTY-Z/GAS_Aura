// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CMCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API ACMCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACMCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> weapon;
};
