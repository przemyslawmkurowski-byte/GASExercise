// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "FabulaCombatSubsystem.generated.h"

class AFabulaCombatArea;
class ICombatController;
class UFabulaAbilitySystemComponent;
/**
 * Experimental subsystem responsible for initializing combat - f.e. changing camera - and for control over turn order.
 */
UCLASS()
class GASEXERCISE_API UFabulaCombatSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void StartCombat(AFabulaCombatArea* InArea, AFabulaParty* InParty0, AFabulaParty* InParty1, APlayerController* InPlayerController, 
		TScriptInterface<ICombatController> InPlayerCombatController, AActor* InEnemyController, APawn* InCameraPawn);

	UFUNCTION(BlueprintCallable)
	void EndTurn();

	UFUNCTION(BlueprintCallable)
	void GetControllerFromComponent(TScriptInterface<ICombatController>& CombatController, UFabulaAbilitySystemComponent* Who);

	UFUNCTION(BlueprintCallable)
	TArray<UFabulaAbilitySystemComponent*> GetCreaturesAvailableForActivation(TScriptInterface<ICombatController> OwningController);
	
	/* Candidate for library */
	UFUNCTION(BlueprintCallable)
	static TArray<FGameplayAbilitySpec> GetAllAbilitiesFromPawn(UFabulaAbilitySystemComponent* Who);
	
	//UFUNCTION(BlueprintCallable, meta=(DeprecatedMessage="Deprecated. Use FabulaHelperLibrary::GetAvailableTargets"))
	//TArray<UFabulaAbilitySystemComponent*> GetAllAvailableTargets(UFabulaAbilitySystemComponent* Who);

	UFUNCTION(BlueprintCallable)
	AFabulaParty* GetOpposingParty(UFabulaAbilitySystemComponent* Caller);
	
private:
	void StartRound();

	UObject* GetCurrentPlayer();
	bool HasAnyCreatureAvailableForActivation(TScriptInterface<ICombatController> OwningController);

	void PositionCreatures(AFabulaParty* InParty, TArray<USceneComponent*> InPositions);


	/* for now - player party */
	UPROPERTY()
	TObjectPtr<AFabulaParty> Party0;
	
	/* for now - enemies */
	UPROPERTY()
	TObjectPtr<AFabulaParty> Party1;

	UPROPERTY()
	TObjectPtr<AActor> EnemyController;

	UPROPERTY()
	TObjectPtr<AActor> PlayerController;

	UPROPERTY()
	TObjectPtr<UObject> PlayerCombatController;

	// control params
	bool bPlayerTurn;
	
	// we depend on old PlayerCharacter not being destroyed during combat.
	UPROPERTY()
	TObjectPtr<APawn> PreviousPlayerPawn;

};
