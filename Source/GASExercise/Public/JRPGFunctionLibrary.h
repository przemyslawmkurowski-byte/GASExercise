// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JRPGFunctionLibrary.generated.h"

/**
 * This class is not really defined at this moment. It is go-to place for every static blueprint function concerning
 * JRPG framework, which is not sustainable of course. It will be broken up when need arise.
 */
UCLASS()
class GASEXERCISE_API UJRPGFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static void SendTargetReadyCallback(FTargetingCallbackAddress InCallbackAddress, TArray<UJRPGAbilitySystemComponent*> InTargets);
	
	UFUNCTION(BlueprintCallable)
	static void SendTargetCancelledCallback(FTargetingCallbackAddress InCallbackAddress);
	
};
