// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& inputTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& action : arr_abilityInputAction)
	{
		if (action.inputAction && action.inputTag == inputTag)
			return action.inputAction;
	}

	if (bLogNotFound)
		UE_LOG(LogTemp, Error, TEXT("can't find AbilityInputAction for InputTag[%s] on InputConfig[%s]"), 
			*inputTag.ToString(), *GetNameSafe(this));

	return nullptr;
}
