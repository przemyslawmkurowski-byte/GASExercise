// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CombatSubsystem.generated.h"

class ICombatController;
class UJRPGAbilitySystemComponent;
/**
 * Experimental subsystem responsible for initializing combat - f.e. changing camera - and for control over turn order.
 */
UCLASS()
class GASEXERCISE_API UCombatSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void StartCombat(TArray<AJRPGCharacter*> TeamA, TArray<AJRPGCharacter*> TeamB, APlayerController* PlayerController, AActor* InEnemyController, APawn* CameraPawn);

	UFUNCTION(BlueprintCallable)
	void EndTurn();

	UFUNCTION(BlueprintCallable)
	void GetControllerFromComponent(TScriptInterface<ICombatController>& CombatController, UJRPGAbilitySystemComponent* Who);

	UFUNCTION(BlueprintCallable)
	TArray<UJRPGAbilitySystemComponent*> GetCreaturesAvailableForActivation(TScriptInterface<ICombatController> OwningController);
	
	/* Candidate for library */
	UFUNCTION(BlueprintCallable)
	static TArray<FGameplayAbilitySpec> GetAllAbilitiesFromPawn(UJRPGAbilitySystemComponent* Who);
	
	UFUNCTION(BlueprintCallable)
	TArray<UJRPGAbilitySystemComponent*> GetAllAvailableTargets(UJRPGAbilitySystemComponent* Who);
	
	
private:
	void StartRound();

	AActor* GetCurrentPlayer();
	bool HasAnyCreatureAvailableForActivation(TScriptInterface<ICombatController> OwningController);


	/* for now - player party */
	UPROPERTY()
	TArray<AJRPGCharacter*> TeamA;
	
	/* for now - enemies */
	UPROPERTY()
	TArray<AJRPGCharacter*> TeamB;

	UPROPERTY()
	TObjectPtr<AActor> EnemyController;

	UPROPERTY()
	TWeakObjectPtr<AActor> PlayerController;

	// control params
	bool bPlayerTurn;
	
	// we depend on old PlayerCharacter not being destroyed during combat.
	UPROPERTY()
	TWeakObjectPtr<APawn> PreviousPlayerPawn;

};
