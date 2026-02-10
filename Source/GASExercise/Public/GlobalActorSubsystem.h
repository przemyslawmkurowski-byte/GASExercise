// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GlobalActorSubsystem.generated.h"

class AFabulaParty;

/**
 * This world subsystem is responsible for holding references to all global actors. Note actors are per definition World-bound, and therefore not
 * 'global' in typical coding sense
 */
UCLASS()
class GASEXERCISE_API UGlobalActorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerParty(AFabulaParty* InParty);

	UFUNCTION(BlueprintPure)
	AFabulaParty* GetPlayerParty();

private:
	UPROPERTY()
	TObjectPtr<AFabulaParty> PlayerParty;

	
};
