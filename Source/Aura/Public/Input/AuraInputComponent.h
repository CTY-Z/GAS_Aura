// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AuraInputConfig.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityAction(const UAuraInputConfig* config, UserClass* object, 
		PressedFuncType pressFunc, ReleasedFuncType releasedFunc, HeldFuncType heldFunc);

};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
inline void UAuraInputComponent::BindAbilityAction(const UAuraInputConfig* config, UserClass* object, PressedFuncType pressFunc, ReleasedFuncType releasedFunc, HeldFuncType heldFunc)
{
	check(config);

	for (const FAuraInputAction& action : config->arr_abilityInputAction)
	{
		if (action.inputAction && action.inputTag.IsValid())
		{
			if (pressFunc)
				BindAction(action.inputAction, ETriggerEvent::Started, object, pressFunc, action.inputTag);

			if (releasedFunc)
				BindAction(action.inputAction, ETriggerEvent::Completed, object, releasedFunc, action.inputTag);

			if (heldFunc)
				BindAction(action.inputAction, ETriggerEvent::Triggered, object, heldFunc, action.inputTag);
		}
	}
}
