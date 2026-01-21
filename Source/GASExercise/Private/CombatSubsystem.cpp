// Fill out your copyright notice in the Description page of Project Settings.
#include "CombatSubsystem.h"

#include "JRPGAbilitySystemComponent.h"
#include "JRPGCharacter.h"
#include "CombatController.h"

void UCombatSubsystem::StartCombat(TArray<AJRPGCharacter*> InTeamA, TArray<AJRPGCharacter*> InTeamB,
                                   APlayerController* InPlayerController, AActor* InEnemyController, APawn* InCameraPawn)
{
	PreviousPlayerPawn = InPlayerController->GetPawnOrSpectator();
	
	TeamA = InTeamA;
	TeamB = InTeamB;
	
	/*
	 * IMPORTANT: these two lines has to be executed as last ones as of now. InCameraPawn depends on combat being
	 * basically started at the moment it is possessed. It should be changed in the future, but for now, at experimental
	 * stage, I can keep it as is.
	 **/
	InPlayerController->UnPossess();
	InPlayerController->Possess(InCameraPawn);
	PlayerController = InPlayerController;

	EnemyController = InEnemyController;

	for(auto* Creature : TeamA)
		Creature->OnRoundStarted();
	for (auto* Creature : TeamB)
		Creature->OnRoundStarted();

	/* According to errata rules, old initiative roll was removed, now Player Party starts combat unless there is at least one Villain present */
	bPlayerTurn = true;
	ICombatController::Execute_StartTurn(PlayerController.Get());
}


void UCombatSubsystem::EndTurn()
{
	if (bPlayerTurn)
	{
		ICombatController::Execute_EndTurn(PlayerController.Get());
	}
	else
	{
		ICombatController::Execute_EndTurn(EnemyController.Get());
	}


	bPlayerTurn = !bPlayerTurn;
	if(bPlayerTurn)
		ICombatController::Execute_StartTurn(PlayerController.Get());
	else
		ICombatController::Execute_StartTurn(EnemyController.Get());
}

void UCombatSubsystem::GetControllerFromComponent(TScriptInterface<ICombatController>& CombatController, UJRPGAbilitySystemComponent* Who)
{
	for (auto* Character : TeamA)
	{
		if (Character != nullptr && Character->GetAbilitySystemComponent() == Who)
		{
			CombatController.SetObject(PlayerController.Get());
			return;
		}
	}
	// else
	for (auto* Character : TeamB)
	{
		if (Character != nullptr && Character->GetAbilitySystemComponent() == Who)
		{
			CombatController.SetObject(EnemyController.Get());
			return;
		}
	}
	//else
	CombatController.SetObject(nullptr);
}

TArray<UJRPGAbilitySystemComponent*> UCombatSubsystem::GetAllPawnsPossibleForActivation()
{
	TArray<UJRPGAbilitySystemComponent*> Ret;
	Ret.Reserve(TeamA.Num());
	for (auto Creature : TeamA)
	{
		Ret.Add(Creature->GetAbilitySystemComponent());
	}
	
	return Ret;
}

TArray<FGameplayAbilitySpec> UCombatSubsystem::GetAllAbilitiesFromPawn(UJRPGAbilitySystemComponent* Who)
{
	return Who->GetActivatableAbilities();
}

TArray<UJRPGAbilitySystemComponent*> UCombatSubsystem::GetAllAvailableTargets(UJRPGAbilitySystemComponent* Who)
{
	TArray<UJRPGAbilitySystemComponent*> Ret;
	Ret.Reserve(TeamB.Num());
	for (auto Creature : TeamB)
	{
		Ret.Add(Creature->GetAbilitySystemComponent());
	}
	
	return Ret;
}