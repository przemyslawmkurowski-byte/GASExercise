// Fill out your copyright notice in the Description page of Project Settings.


#include "FabulaAbilitySystemComponent.h"

#include "FabulaAttributeSet.h"

bool UFabulaAbilitySystemComponent::HasTurns()
{
	auto Attributes = Cast<UFabulaAttributeSet>(GetAttributeSet(UFabulaAttributeSet::StaticClass()));
	return Attributes->GetTurns() > 0;
}

void UFabulaAbilitySystemComponent::SetParty(AFabulaParty* InParty)
{
	Party = InParty;
}

AFabulaParty* UFabulaAbilitySystemComponent::GetParty()
{
	return Party;
}