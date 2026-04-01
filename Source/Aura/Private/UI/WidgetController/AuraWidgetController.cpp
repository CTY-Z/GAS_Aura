// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& params)
{
	playerCtrl = params.playerCtrl;
	playerState = params.playerState;
	asc = params.asc;
	attributeSet = params.attributeSet;
}
