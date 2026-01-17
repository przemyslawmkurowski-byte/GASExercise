// Fill out your copyright notice in the Description page of Project Settings.


#include "JRPGFunctionLibrary.h"

#include "AbilityTask_JRPGTargetting.h"

void UJRPGFunctionLibrary::SendTargetReadyCallback(FTargetingCallbackAddress InCallbackAddress,
                                                   TArray<UJRPGAbilitySystemComponent*> InTargets)
{
	TWeakObjectPtr<UAbilityTask_JRPGTargetting> AddressAsWeak = InCallbackAddress.CallbackAddress;
	
	if (UAbilityTask_JRPGTargetting* Address = AddressAsWeak.Get())
	{
		Address->OnTargetDataReadyCallback(InTargets);
	}
}
	

void UJRPGFunctionLibrary::SendTargetCancelledCallback(FTargetingCallbackAddress InCallbackAddress)
{
	TWeakObjectPtr<UAbilityTask_JRPGTargetting> AddressAsWeak = InCallbackAddress.CallbackAddress;
	
	if (UAbilityTask_JRPGTargetting* Address = AddressAsWeak.Get())
	{
		Address->OnTargetDataCancelledCallback();
	}
}