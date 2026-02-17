// Fill out your copyright notice in the Description page of Project Settings.

#include "FabulaCombatSubsystem.h"

#include "FabulaAbilitySystemComponent.h"
#include "FabulaCharacter.h"
#include "FabulaCombatArea.h"
#include "FabulaParty.h"
#include "CombatController.h"

void UFabulaCombatSubsystem::StartCombat(AFabulaCombatArea* InArea, AFabulaParty* InParty0, AFabulaParty* InParty1,
                                   APlayerController* InPlayerController, TScriptInterface<ICombatController> InPlayerCombatController,
	AActor* InEnemyController, APawn* InCameraPawn)
{
	if (InParty0 == nullptr || InParty1 == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot initialize Combat, at least one Party is null"));
		return;
	}


	PreviousPlayerPawn = InPlayerController->GetPawnOrSpectator();
	
	Party0 = InParty0;
	Party1 = InParty1;
	
	PlayerController = InPlayerController;
	PlayerCombatController = InPlayerCombatController.GetObject();

	EnemyController = InEnemyController;

	/* 
	* temporary solution : Pawns are hard-on teleported to their expected position. Proper way would be to make this logic latent, and handle editor-side
	*/ 
	PositionCreatures(Party0, InArea->GetCombatPositionsForParty0());
	PositionCreatures(Party1, InArea->GetCombatPositionsForParty1());

	/* According to errata rules, old initiative roll was removed, now Player Party starts combat unless there is at least one Villain present */
	bPlayerTurn = true;

	/*
	* IMPORTANT: these two lines has to be executed as last ones as of now. InCameraPawn depends on combat being
	* basically started at the moment it is possessed. It should be changed in the future, but for now, at experimental
	* stage, I can keep it as is.
	**/
	InPlayerController->UnPossess();
	InPlayerController->Possess(InCameraPawn);

	for (auto Creature : Party0->GetAllCreatures())
		Creature->OnCombatStarted.Broadcast();
	for (auto Creature : Party1->GetAllCreatures())
		Creature->OnCombatStarted.Broadcast();

	StartRound();
}

void UFabulaCombatSubsystem::PositionCreatures(AFabulaParty* InParty, TArray<USceneComponent*> InPositions)
{
	TArray<UFabulaAbilitySystemComponent*> Creatures = InParty->GetAllCreatures();

	for (int i = 0; i < InPositions.Num() && i < Creatures.Num(); ++i)
	{
		Creatures[i]->GetAvatarActor()->SetActorTransform(InPositions[i]->GetComponentTransform());
	}
}

void UFabulaCombatSubsystem::StartRound()
{
	for (auto Creature : Party0->GetAllCreatures())
		Creature->OnRoundStarted.Broadcast();
	for (auto Creature : Party1->GetAllCreatures())
		Creature->OnRoundStarted.Broadcast();
	bPlayerTurn = true;
	ICombatController::Execute_StartTurn(PlayerCombatController);
}


void UFabulaCombatSubsystem::EndTurn()
{
	// inform controller that its turn has succesfully ended
	if (bPlayerTurn)
	{
		ICombatController::Execute_EndTurn(PlayerCombatController);
	}
	else
	{
		ICombatController::Execute_EndTurn(EnemyController);
	}

	/// swap current player
	bPlayerTurn = !bPlayerTurn;

	// give turn to new current player, if they have any activable creature
	UObject* CurrentPlayer = GetCurrentPlayer();
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

UObject* UFabulaCombatSubsystem::GetCurrentPlayer()
{
	return bPlayerTurn ? PlayerCombatController : EnemyController;
}

void UFabulaCombatSubsystem::GetControllerFromComponent(TScriptInterface<ICombatController>& CombatController, UFabulaAbilitySystemComponent* Who)
{
	if (Party0->Contains(Who))
	{
		CombatController.SetObject(PlayerCombatController);
	}
	else if (Party1->Contains(Who))
	{
		CombatController.SetObject(EnemyController);
	}
	else
	{
		CombatController.SetObject(nullptr);
	}
}

TArray<UFabulaAbilitySystemComponent*> UFabulaCombatSubsystem::GetCreaturesAvailableForActivation(TScriptInterface<ICombatController> OwningController)
{
	TWeakObjectPtr<AFabulaParty> Working = OwningController == PlayerController ? Party0 : Party1;
	return Working.Get()->GetAllCreaturesWithAtLeastOneTurn();
}

bool UFabulaCombatSubsystem::HasAnyCreatureAvailableForActivation(TScriptInterface<ICombatController> OwningController)
{
	// TODO: optimise this code
	return GetCreaturesAvailableForActivation(OwningController).Num() > 0;
}

TArray<FGameplayAbilitySpec> UFabulaCombatSubsystem::GetAllAbilitiesFromPawn(UFabulaAbilitySystemComponent* Who)
{
	return Who->GetActivatableAbilities();
}

AFabulaParty* UFabulaCombatSubsystem::GetOpposingParty(UFabulaAbilitySystemComponent* Caller)
{
	auto* CallerParty = Caller->GetParty();
	return CallerParty == Party0 ? Party1 : Party0;
}