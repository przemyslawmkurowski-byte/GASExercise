// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "FabulaAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFabulaGenericEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundStarted);

class AFabulaParty;

/**
 * Object that represent single Creature in all Fabula systems.
 */
UCLASS()
class GASEXERCISE_API UFabulaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetParty(AFabulaParty* InParty);

	UFUNCTION(BlueprintPure)
	bool HasTurns();

	UFUNCTION(BlueprintPure)
	bool IsAlive();

	UFUNCTION(BlueprintPure)
	AFabulaParty* GetParty();

	UFUNCTION(BlueprintPure)
	FText GetDisplayName() { return DisplayName; }

	UPROPERTY(BlueprintAssignable)
	FOnRoundStarted OnCombatStarted;

	UPROPERTY(BlueprintAssignable)
	FOnRoundStarted OnRoundStarted;

	/* UX interface */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FFabulaGenericEvent StartShoulderMountedCamera;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FFabulaGenericEvent StopShoulderMountedCamera;

	UFUNCTION(BlueprintCallable)
	void SetGuardEffectHandlers(const FActiveGameplayEffectHandle& InSelfEffect, const FActiveGameplayEffectHandle& InTargetEffect);

	// called after CommitAbility, but before anything else. Dirty hack.
	UFUNCTION(BlueprintCallable)
	void ActivateCreature();

	UFUNCTION(BlueprintCallable)
	void HandleDeath();

private:
	// guard block
	UPROPERTY()
	FActiveGameplayEffectHandle GuardEffectSelf;

	UPROPERTY()
	FActiveGameplayEffectHandle TargetEffectSelf;


	UPROPERTY(EditAnywhere)
	FText DisplayName;

	/* Because basic params are GameplayEffect in GAS, it seems */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> InitData;

	/* Will be automatially set by FabulaParty */
	UPROPERTY(VisibleAnywhere)
	AFabulaParty* Party;
	
};
