// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "AbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

ACMCharacter::ACMCharacter()
{
	UCharacterMovementComponent* movementComp = GetCharacterMovement();

	movementComp->bOrientRotationToMovement = true;
	movementComp->RotationRate = FRotator(0.f, 400.f, 0.f);
	movementComp->bConstrainToPlane = true;
	movementComp->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ACMCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void ACMCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Client
	InitAbilityActorInfo();
}

int32 ACMCharacter::GetPlayerLevel()
{
	const AAuraPlayerState* auraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(auraPlayerState);

	return auraPlayerState->GetPlayerLevel();
}

void ACMCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* auraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(auraPlayerState);
	auraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(auraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(auraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	asc = auraPlayerState->GetAbilitySystemComponent();
	attributeSet = auraPlayerState->GetAttributeSet();

	if (auto ctrl = Cast<AAuraPlayerController>(GetController()))
	{
		if (auto auraHUD = Cast<AAuraHUD>(ctrl->GetHUD()))
			auraHUD->InitOverlay(ctrl, auraPlayerState, asc, attributeSet);
	}

	InitializeDefaultAttributes();
}
