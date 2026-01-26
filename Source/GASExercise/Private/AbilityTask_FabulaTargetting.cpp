// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityTask_FabulaTargetting.h"

#include "CombatController.h"
#include "FabulaCombatSubsystem.h"
#include "FabulaHelperLibrary.h"

UAbilityTask_FabulaTargetting* UAbilityTask_FabulaTargetting::FabulaWaitForTarget(UGameplayAbility* OwningAbility,
	FName TaskInstanceName,
	const FTargetingParams& InParams)
{
	UAbilityTask_FabulaTargetting* MyObj = NewAbilityTask<UAbilityTask_FabulaTargetting>(OwningAbility, TaskInstanceName);
	MyObj->Params = InParams;
	return MyObj;
}

void UAbilityTask_FabulaTargetting::Activate()
{
	// TODO: actually implement communication with CombatSystem, demand targetting etc
	UFabulaCombatSubsystem* CombatSystem = GetWorld()->GetSubsystem<UFabulaCombatSubsystem>();
	TArray<UFabulaAbilitySystemComponent*> Targets = UFabulaHelperLibrary::GetAvailableTargets(CombatSystem, Params.Source, Params.AllowedTargets);

	// CombatSystem->GetAllAvailableTargets(Params.Source);
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

void UAbilityTask_FabulaTargetting::OnTargetDataReadyCallback(TArray<UFabulaAbilitySystemComponent*> InTargets)
{
	Accepted.Broadcast(InTargets);
}

void UAbilityTask_FabulaTargetting::OnTargetDataCancelledCallback()
{
	Cancelled.Broadcast(EmptyArray);
}

void UAbilityTask_FabulaTargetting::OnDestroy(bool AbilityEnded)
{
	// TODO: clear all references

	Super::OnDestroy(AbilityEnded);
}