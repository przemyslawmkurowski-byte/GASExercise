// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <AttributeSet.h>
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FabulaHelperLibrary.generated.h"

class AFabulaCharacter;
class UFabulaAbilitySystemComponent;
class UFabulaCombatSubsystem;

/**
 * General-purpose library for different functions needed to coordinate with GAS 
 */
UCLASS()
class GASEXERCISE_API UFabulaHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* Check is ttrpg term. Strange way of returning result is because of how it looks blueprint-side */
	UFUNCTION(BlueprintCallable)
	static void BasicCheck(UAbilitySystemComponent* InCreature, FGameplayAttribute InAttribute0, FGameplayAttribute InAttribute1, int InDifficulty,
		bool& Success, int& HighRoll, bool& IsCritical);

	UFUNCTION(BlueprintCallable)
	static TArray<UFabulaAbilitySystemComponent*> GetAvailableTargets(UFabulaCombatSubsystem* InContext, UFabulaAbilitySystemComponent* InCaller,
		ETargetType InTargetType, bool InAllowTargettingDeadCreatures);
	
};
