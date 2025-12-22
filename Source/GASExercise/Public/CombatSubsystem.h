// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CombatSubsystem.generated.h"

/**
 * Experimental subsystem responsible for initializing combat - f.e. changing camera - and for control over turn order.
 */
UCLASS()
class GASEXERCISE_API UCombatSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void StartCombat(TArray<AJRPGCharacter*> TeamA, TArray<AJRPGCharacter*> TeamB, APlayerController* PlayerController, APawn* CameraPawn);
	
	UFUNCTION(BlueprintCallable)
	TArray<UJRPGAbilitySystemComponent*> GetAllPawnsPossibleForActivation();
	
	UFUNCTION(BlueprintCallable)
	TArray<FGameplayAbilitySpec> GetAllAbilitiesFromPawn(UJRPGAbilitySystemComponent* Who);
	
	UFUNCTION(BlueprintCallable)
	TArray<UJRPGAbilitySystemComponent*> GetAllAvailableTargets(UJRPGAbilitySystemComponent* Who);
	
	
private:
	/* for now - player party */
	UPROPERTY()
	TArray<AJRPGCharacter*> TeamA;
	
	/* for now - enemies */
	UPROPERTY()
	TArray<AJRPGCharacter*> TeamB;
	
	// we depend on old PlayerCharacter not being destroyed during combat.
	UPROPERTY()
	APawn* PreviousPlayerPawn;
	
};
