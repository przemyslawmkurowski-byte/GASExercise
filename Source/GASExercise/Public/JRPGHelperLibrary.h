// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <AttributeSet.h>
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JRPGHelperLibrary.generated.h"


/**
 * General-purpose library for different functions needed to coordinate with GAS 
 */
UCLASS()
class GASEXERCISE_API UJRPGHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* Check is ttrpg term. Strange way of returning result is because of how it looks blueprint-side */
	UFUNCTION(BlueprintCallable)
	static void BasicCheck(UAbilitySystemComponent* Creature, FGameplayAttribute InAttribute0, FGameplayAttribute InAttribute1, int InDifficulty,
		bool& Success, int& HighRoll, bool& IsCritical);
	
};
