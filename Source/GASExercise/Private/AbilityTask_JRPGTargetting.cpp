// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTask_JRPGTargetting.h"

#include "CombatSubsystem.h"

UAbilityTask_JRPGTargetting* UAbilityTask_JRPGTargetting::JRPGWaitForTarget(UGameplayAbility* OwningAbility,
	FName TaskInstanceName,
	UJRPGAbilitySystemComponent* InSource,
    ETargetType PreferredTargets,
    ETargetType AllowedTargets,
    int MaxNumberOfTargets,
    float CostPerTarget,
    bool bCostScalesByNumberOfTargets)
{
	UAbilityTask_JRPGTargetting* MyObj = NewAbilityTask<UAbilityTask_JRPGTargetting>(OwningAbility, TaskInstanceName);
	MyObj->Source = InSource;
	return MyObj;
}

void UAbilityTask_JRPGTargetting::Activate()
{
	// TODO: actually implement communication with CombatSystem, demand targetting etc
	auto* CombatSystem = GetWorld()->GetSubsystem<UCombatSubsystem>();
	//auto* CombatSystem
	
	checkNoEntry();
}

void UAbilityTask_JRPGTargetting::OnDestroy(bool AbilityEnded)
{
	// TODO: clear all references

	Super::OnDestroy(AbilityEnded);
}