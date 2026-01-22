// Fill out your copyright notice in the Description page of Project Settings.


#include "JRPGAbilitySystemComponent.h"

#include "JRPGAttributeSet.h"

bool UJRPGAbilitySystemComponent::HasTurns()
{
	auto Attributes = Cast<UJRPGAttributeSet>(GetAttributeSet(UJRPGAttributeSet::StaticClass()));
	return Attributes->GetTurns() > 0;
}