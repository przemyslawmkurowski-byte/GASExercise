// Fill out your copyright notice in the Description page of Project Settings.


#include "FabulaFunctionLibrary.h"

#include "AbilityTask_FabulaTargetting.h"

void UFabulaFunctionLibrary::SendTargetReadyCallback(FTargetingCallbackAddress InCallbackAddress,
                                                   TArray<UFabulaAbilitySystemComponent*> InTargets)
{
	TWeakObjectPtr<UAbilityTask_FabulaTargetting> AddressAsWeak = InCallbackAddress.CallbackAddress;
	
	if (UAbilityTask_FabulaTargetting* Address = AddressAsWeak.Get())
	{
		Address->OnTargetDataReadyCallback(InTargets);
	}
}
	

void UFabulaFunctionLibrary::SendTargetCancelledCallback(FTargetingCallbackAddress InCallbackAddress)
{
	TWeakObjectPtr<UAbilityTask_FabulaTargetting> AddressAsWeak = InCallbackAddress.CallbackAddress;
	
	if (UAbilityTask_FabulaTargetting* Address = AddressAsWeak.Get())
	{
		Address->OnTargetDataCancelledCallback();
	}
}