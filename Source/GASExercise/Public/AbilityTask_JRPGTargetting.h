// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_JRPGTargetting.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FJRPGTargettingDelegate, const TArray<UJRPGAbilitySystemComponent*>&, Targets);

UENUM()
enum class ETargetType : uint8
{
	ETT_Self,
	ETT_Ally,
	ETT_SelfOrAlly,
	ETT_Enemy,
	ETT_Any
};


/**
 * Experimental Ability. It should contact CombatSubsystem, demand target for ability, and wait until it is provided
 */
UCLASS()
class GASEXERCISE_API UAbilityTask_JRPGTargetting : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FJRPGTargettingDelegate Accepted;
	
	UPROPERTY(BlueprintAssignable)
	FJRPGTargettingDelegate Cancelled;
	
	/** Spawns target actor and waits for it to return valid data or to be canceled. */
	UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms="Instigator"), Category="Ability|Tasks")
	static UAbilityTask_JRPGTargetting* JRPGWaitForTarget(UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		UJRPGAbilitySystemComponent* Source,
		ETargetType PreferredTargets,
		ETargetType AllowedTargets,
		int MaxNumberOfTargets,
		float CostPerTarget,
		bool bCostScalesByNumberOfTargets);
	
	virtual void Activate() override;
	
	virtual void OnDestroy(bool AbilityEnded) override;
	
private:
	// callbacks
	void OnTargetDataReadyCallback(TArray<UJRPGAbilitySystemComponent*> InTargets);
	void OnTargetDataCancelledCallback();
	
	// member variables
	UPROPERTY()
	UJRPGAbilitySystemComponent* Source;
};
