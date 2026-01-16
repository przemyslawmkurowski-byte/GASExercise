// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTask_JRPGTargetting.h"

#include "CombatSubsystem.h"

UAbilityTask_JRPGTargetting* UAbilityTask_JRPGTargetting::JRPGWaitForTarget(UGameplayAbility* OwningAbility,
	FName TaskInstanceName,
	const FTargetingParams& Params)
{
	UAbilityTask_JRPGTargetting* MyObj = NewAbilityTask<UAbilityTask_JRPGTargetting>(OwningAbility, TaskInstanceName);
	MyObj->Source = Params.Source;
	return MyObj;
}

void UAbilityTask_JRPGTargetting::Activate()
{
	// TODO: actually implement communication with CombatSystem, demand targetting etc
	UCombatSubsystem* CombatSystem = GetWorld()->GetSubsystem<UCombatSubsystem>();
	TArray<UJRPGAbilitySystemComponent*> Targets = CombatSystem->GetAllAvailableTargets(Source.Get());
	TScriptInterface<ICombatController> SourceController = nullptr;
	CombatSystem->GetControllerFromComponent(SourceController, Source.Get());

	//auto* CombatSystem
	
	checkNoEntry("Not implemented yet.");
}

void UAbilityTask_JRPGTargetting::OnDestroy(bool AbilityEnded)
{
	// TODO: clear all references

	Super::OnDestroy(AbilityEnded);
}