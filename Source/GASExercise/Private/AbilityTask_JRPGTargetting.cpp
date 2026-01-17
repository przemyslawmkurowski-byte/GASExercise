// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityTask_JRPGTargetting.h"

#include "CombatSubsystem.h"
#include "CombatController.h"

UAbilityTask_JRPGTargetting* UAbilityTask_JRPGTargetting::JRPGWaitForTarget(UGameplayAbility* OwningAbility,
	FName TaskInstanceName,
	const FTargetingParams& InParams)
{
	UAbilityTask_JRPGTargetting* MyObj = NewAbilityTask<UAbilityTask_JRPGTargetting>(OwningAbility, TaskInstanceName);
	MyObj->Params = InParams;
	return MyObj;
}

void UAbilityTask_JRPGTargetting::Activate()
{
	// TODO: actually implement communication with CombatSystem, demand targetting etc
	UCombatSubsystem* CombatSystem = GetWorld()->GetSubsystem<UCombatSubsystem>();
	TArray<UJRPGAbilitySystemComponent*> Targets = CombatSystem->GetAllAvailableTargets(Params.Source);
	TScriptInterface<ICombatController> SourceController = nullptr;
	CombatSystem->GetControllerFromComponent(SourceController, Params.Source);

	if (SourceController.GetObject() == nullptr)
	{
		// todo: handle this case
		return;
	}

	ICombatController::Execute_GetTargets(SourceController.GetObject(), Params, FTargetingCallbackAddress(this));

	//SourceController->GetTargets();

	//auto* CombatSystem
	
}

void UAbilityTask_JRPGTargetting::OnTargetDataReadyCallback(TArray<UJRPGAbilitySystemComponent*> InTargets)
{
	Accepted.Broadcast(InTargets);
}

void UAbilityTask_JRPGTargetting::OnTargetDataCancelledCallback()
{
	Cancelled.Broadcast(EmptyArray);
}

void UAbilityTask_JRPGTargetting::OnDestroy(bool AbilityEnded)
{
	// TODO: clear all references

	Super::OnDestroy(AbilityEnded);
}