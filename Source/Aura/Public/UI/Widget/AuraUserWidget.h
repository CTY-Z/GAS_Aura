// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* inWidgetCtrl);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> widgetCtrl;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
