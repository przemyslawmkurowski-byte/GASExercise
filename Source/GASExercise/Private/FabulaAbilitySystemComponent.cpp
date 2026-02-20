// Fill out your copyright notice in the Description page of Project Settings.


#include "FabulaAbilitySystemComponent.h"

#include "FabulaAttributeSet.h"

void UFabulaAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	if (InitData == nullptr)
	{
		UE_LOG(LogTemp, Error, L"Init data not set");
		return;
	}

	// Oh, screw it.
	auto EffectContext = MakeEffectContext();
	BP_ApplyGameplayEffectToSelf(InitData, 1, EffectContext);
}

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

void UFabulaAbilitySystemComponent::SetGuardEffectHandlers(const FActiveGameplayEffectHandle& InSelfEffect, const FActiveGameplayEffectHandle& InTargetEffect)
{
	GuardEffectSelf = InSelfEffect;
	TargetEffectSelf = InTargetEffect;
}

void UFabulaAbilitySystemComponent::ActivateCreature()
{
	RemoveActiveGameplayEffect(GuardEffectSelf);
	if (TargetEffectSelf.IsValid())
	{
		auto Target = TargetEffectSelf.GetOwningAbilitySystemComponent();
		if (Target != nullptr)
			Target->RemoveActiveGameplayEffect(TargetEffectSelf);
	}

}