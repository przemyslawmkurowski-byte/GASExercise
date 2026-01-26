// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <AttributeSet.h>
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FabulaHelperLibrary.generated.h"

class AFabulaCharacter;
class UFabulaAbilitySystemComponent;
class UFabulaCombatSubsystem;

UENUM()
enum class ERollSpecialResult : uint8
{
	None,
	Fumble,
	CriticalSuccess
};

/**
 * General-purpose library for different functions needed to coordinate with GAS 
 */
UCLASS()
class GASEXERCISE_API UFabulaHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*
	* Standard roll used in Fabula Ultima checks. Check is ttrpg term.
	* I do not do Result vs Difficulty comparison here, as sometimes we tes one roll against more than one Difficulty (f.e. Multiattack).
	* Strange way of returning result is because of how it looks blueprint-side
	*/
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "OutSpecialResult"))
	static void BasicRoll(UAbilitySystemComponent * InCreature, FGameplayAttribute InAttribute0, FGameplayAttribute InAttribute1,
		int InModifier, int& OutResult, int& OutHighRoll, ERollSpecialResult& OutSpecialResult);

	UFUNCTION(BlueprintCallable)
	static TArray<UFabulaAbilitySystemComponent*> GetAvailableTargets(UFabulaCombatSubsystem* InContext, UFabulaAbilitySystemComponent* InCaller,
		ETargetType InTargetType, bool InAllowTargettingDeadCreatures);
	
};
