// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatController.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatController : public UInterface
{
	GENERATED_BODY()
};

/**
 * Experimental class. This 'Controller' represent player when interacting with CombatSystem. Note, against its name, it
 * is NOT AController, through it fills similar role in Fabula framework that AController in Unreal framework.
 */
class GASEXERCISE_API ICombatController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent)
	void StartTurn();

	UFUNCTION(BlueprintImplementableEvent)
	void EndTurn();


	UFUNCTION(BlueprintImplementableEvent, meta=(DeprecationMessage="Use FabulaHelperLibrary::GetAvailableTargets instead"))
	void GetTargets(const FTargetingParams& InParams, FTargetingCallbackAddress InCallbackAddress);
};
