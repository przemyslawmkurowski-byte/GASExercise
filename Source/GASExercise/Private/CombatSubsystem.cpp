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
	
	PlayerController = InPlayerController;

	EnemyController = InEnemyController;

	/* According to errata rules, old initiative roll was removed, now Player Party starts combat unless there is at least one Villain present */
	bPlayerTurn = true;

	/*
	* IMPORTANT: these two lines has to be executed as last ones as of now. InCameraPawn depends on combat being
	* basically started at the moment it is possessed. It should be changed in the future, but for now, at experimental
	* stage, I can keep it as is.
	**/
	InPlayerController->UnPossess();
	InPlayerController->Possess(InCameraPawn);

	StartRound();
}

void UCombatSubsystem::StartRound()
{
	for (auto* Creature : TeamA)
		Creature->OnRoundStarted();
	for (auto* Creature : TeamB)
		Creature->OnRoundStarted();
	ICombatController::Execute_StartTurn(PlayerController.Get());
}


void UCombatSubsystem::EndTurn()
{
	// inform controller that its turn has succesfully ended
	if (bPlayerTurn)
	{
		ICombatController::Execute_EndTurn(PlayerController.Get());
	}
	else
	{
		ICombatController::Execute_EndTurn(EnemyController.Get());
	}

	/// swap current player
	bPlayerTurn = !bPlayerTurn;

	// give turn to new current player, if they have any activable creature
	AActor* CurrentPlayer = GetCurrentPlayer();
	if (HasAnyCreatureAvailableForActivation(CurrentPlayer))
	{
		ICombatController::Execute_StartTurn(CurrentPlayer);
		return;
	}
	//if current player doesn;t have any more activable Creatures, give turn to previous one
	bPlayerTurn = !bPlayerTurn;
	CurrentPlayer = GetCurrentPlayer();
	if (HasAnyCreatureAvailableForActivation(CurrentPlayer))
	{
		ICombatController::Execute_StartTurn(CurrentPlayer);
		return;
	}
	// if all Creatures already moved, start nex round
	StartRound();
}

AActor* UCombatSubsystem::GetCurrentPlayer()
{
	return bPlayerTurn ? PlayerController.Get() : EnemyController.Get();
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

TArray<UJRPGAbilitySystemComponent*> UCombatSubsystem::GetCreaturesAvailableForActivation(TScriptInterface<ICombatController> OwningController)
{
	TArray<AJRPGCharacter*>& Working = OwningController == PlayerController.Get() ? TeamA : TeamB;

	TArray<UJRPGAbilitySystemComponent*> Ret;
	Ret.Reserve(Working.Num());
	for (auto Creature : Working)
	{
		auto Component = Creature->GetAbilitySystemComponent();
		if(Component->HasTurns())
			Ret.Add(Component);
	}

	return Ret;
}

bool UCombatSubsystem::HasAnyCreatureAvailableForActivation(TScriptInterface<ICombatController> OwningController)
{
	TArray<AJRPGCharacter*>& Working = OwningController == PlayerController.Get() ? TeamA : TeamB;

	for (auto Creature : Working)
	{
		auto Component = Creature->GetAbilitySystemComponent();
		if (Component->HasTurns())
			return true;
	}

	return false;
}

TArray<FGameplayAbilitySpec> UCombatSubsystem::GetAllAbilitiesFromPawn(UJRPGAbilitySystemComponent* Who)
{
	return Who->GetActivatableAbilities();
}

TArray<UJRPGAbilitySystemComponent*> UCombatSubsystem::GetAllAvailableTargets(UJRPGAbilitySystemComponent* Who)
{
	AActor* OwningActor = Who->GetOwner();
	TArray<AJRPGCharacter*> Working;
	if (TeamA.Contains(OwningActor))
	{
		Working = TeamB;
	}
	else if (TeamB.Contains(OwningActor))
	{
		Working = TeamA;
	}

	TArray<UJRPGAbilitySystemComponent*> Ret;
	Ret.Reserve(Working.Num());
	for (auto Creature : Working)
	{
		Ret.Add(Creature->GetAbilitySystemComponent());
	}
	
	return Ret;
}