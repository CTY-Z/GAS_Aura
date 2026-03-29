// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(mesh);
	sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFormSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ascInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		auto result = ascInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass());
		const UAuraAttributeSet* auraAttributeSet = Cast<UAuraAttributeSet>(result);

		//todo: !!
		UAuraAttributeSet* mutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(auraAttributeSet);
		mutableAuraAttributeSet->Sethealth(auraAttributeSet->Gethealth() + 25.f);

		Destroy();
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

