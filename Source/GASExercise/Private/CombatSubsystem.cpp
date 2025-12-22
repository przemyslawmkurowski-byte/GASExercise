// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSubsystem.h"

#include "JRPGAbilitySystemComponent.h"
#include "JRPGCharacter.h"

void UCombatSubsystem::StartCombat(TArray<AJRPGCharacter*> InTeamA, TArray<AJRPGCharacter*> InTeamB,
                                   APlayerController* InPlayerController, APawn* InCameraPawn)
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