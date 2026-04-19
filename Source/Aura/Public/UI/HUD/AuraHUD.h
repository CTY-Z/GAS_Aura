// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;
struct FWidgetControllerParams;

class APlayerController;
class APlayerState;
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:


	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& params);
	void InitOverlay(APlayerController* pc, APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& params);


private:

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> overlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> overlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> overlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> overlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> attributeMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> attributeMenuWidgetControllerClass;
};
