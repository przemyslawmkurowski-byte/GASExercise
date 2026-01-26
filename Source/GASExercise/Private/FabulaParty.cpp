// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FabulaParty.h"

#include "FabulaCharacter.h"

void AFabulaParty::BeginPlay()
{
	Super::BeginPlay();

	for (auto Actor : CreaturesAsActors)
	{
		if (Actor)
		{
			UFabulaAbilitySystemComponent* Creature = Actor->GetAbilitySystemComponent();
			Creature->SetParty(this);
			Creatures.Add(Creature);
		}
	}
}

TArray<UFabulaAbilitySystemComponent*> AFabulaParty::GetAllCreatures()
{
	return Creatures;
}

bool AFabulaParty::Contains(UFabulaAbilitySystemComponent* InObj)
{
	return Creatures.Contains(InObj);
}

TArray<UFabulaAbilitySystemComponent*> AFabulaParty::GetAllCreaturesWithAtLeastOneTurn()
{
	TArray<UFabulaAbilitySystemComponent*> Ret;
	Ret.Reserve(Creatures.Num());
	for (auto Creature : Creatures)
	{
		if (Creature && Creature->HasTurns())
			Ret.Add(Creature);
	}
	return Ret;
}