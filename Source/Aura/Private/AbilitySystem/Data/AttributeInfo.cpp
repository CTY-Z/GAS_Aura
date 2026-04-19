// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& tag, bool bLogNotFound) const
{
	for (auto info : arr_attributeInfo)
	{
		if (info.attributeTag == tag)
			return info;
	}

	if (bLogNotFound)
		UE_LOG(LogTemp, Error, TEXT("Can't find info for tag [%s] on AttributeInfo [%s]"), 
			*tag.ToString(), *GetNameSafe(this));

	return FAuraAttributeInfo();
}
