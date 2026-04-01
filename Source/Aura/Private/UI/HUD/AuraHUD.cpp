// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& params)
{
	if (overlayWidgetController == nullptr)
	{
		overlayWidgetController = NewObject<UOverlayWidgetController>(this, overlayWidgetControllerClass);
		overlayWidgetController->SetWidgetControllerParams(params);
		overlayWidgetController->BindCallbackToDependencies();
	}

	return overlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* pc, APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as)
{
	checkf(overlayWidgetClass, TEXT("overlay widget class uninitialized, please fill out BP_AuraHUD"));
	checkf(overlayWidgetControllerClass, TEXT("overlay widget controller class uninitialized, please fill out BP_AuraHUD"));

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), overlayWidgetClass);
	overlayWidget = Cast<UAuraUserWidget>(widget);
	
	const FWidgetControllerParams params(pc, ps, asc, as);
	auto ctrl = GetOverlayWidgetController(params);

	overlayWidget->SetWidgetController(ctrl);
	ctrl->BroadcastInitialValues();
	widget->AddToViewport();
}
