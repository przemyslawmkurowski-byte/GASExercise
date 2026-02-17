// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FabulaAbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_FabulaTargetting.generated.h"

class AFabulaCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFabulaTargettingDelegate, const TArray<UFabulaAbilitySystemComponent*>&, Targets);

UENUM(BlueprintType)
enum class ETargetType : uint8
{
	ETT_Self,
	ETT_Ally,
	ETT_SelfOrAlly,
	ETT_Enemy,
	ETT_Any
};

/*
 * Struct used to pass Targetting Request params
 */
USTRUCT(BlueprintType)
struct FTargetingParams
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	UFabulaAbilitySystemComponent* Source = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	ETargetType PrimaryTargets = ETargetType::ETT_Enemy;
	
	UPROPERTY(BlueprintReadWrite)
	int MaxNumberOfTargets = 1;
	
	UPROPERTY(BlueprintReadWrite)
	float CostPerTarget = 0;
	
	UPROPERTY(BlueprintReadWrite)
	bool bCostScalesByNumberOfTargets = true;
};

USTRUCT(BlueprintType)
struct FTargetingCallbackAddress
{
	GENERATED_BODY()
	
	FTargetingCallbackAddress() {}
	
	FTargetingCallbackAddress(UAbilityTask_FabulaTargetting* InAddress) : CallbackAddress(InAddress) {}
	
	TWeakObjectPtr<UAbilityTask_FabulaTargetting> CallbackAddress;
};

/**
 * Experimental Ability. It should contact CombatSubsystem, demand target for ability, and wait until it is provided
 */
UCLASS()
class GASEXERCISE_API UAbilityTask_FabulaTargetting : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FFabulaTargettingDelegate Accepted;
	
	UPROPERTY(BlueprintAssignable)
	FFabulaTargettingDelegate Cancelled;
	
	/** Spawns target actor and waits for it to return valid data or to be canceled. */
	UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms="Instigator"), Category="Ability|Tasks")
	static UAbilityTask_FabulaTargetting* FabulaWaitForTarget(UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		const FTargetingParams& Params,
		bool InAllowTargettingDeadCreatures);
	
	virtual void Activate() override;
	
	virtual void OnDestroy(bool AbilityEnded) override;
	
	public:
	// callbacks. No, I am not proud of myself. But at this stage I want the system up and running.
	// Making it architecturally-acceptable is planned for second iteration
	void OnTargetDataReadyCallback(TArray<UFabulaAbilitySystemComponent*> InTargets);
	void OnTargetDataCancelledCallback();
	
private:
	UPROPERTY()
	FTargetingParams Params;

	bool bAllowTargettingDeadCreatures;

	// HACK! This one is returned when cancelling targetitng, because we have to return >something<
	// TODO: replace it with specialized struct, that wil lhold array in itself.
	UPROPERTY()
	TArray<UFabulaAbilitySystemComponent*> EmptyArray;
};
