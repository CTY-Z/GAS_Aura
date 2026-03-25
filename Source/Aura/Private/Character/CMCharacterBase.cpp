// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMCharacterBase.h"

ACMCharacterBase::ACMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

