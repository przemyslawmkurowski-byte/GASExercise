// Fill out your copyright notice in the Description page of Project Settings.

#include "FabulaAttributeSet.h"

#include "GameplayEffectExtension.h"

UFabulaAttributeSet::UFabulaAttributeSet()
{
	InitLevel(5);
	InitHP(70);
	InitMaxHP(70);
	InitTurnsPerRound(1);

	InitDexterityDice(8);
	InitInsightDice(8);
	InitMightDice(8);
	InitWillpowerDice(8);

	InitDamageReduction(0);
	InitPrimaryWeaponDamage(8);
}

void UFabulaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHP());
	}

	Super::PreAttributeChange(Attribute, NewValue);
}

void UFabulaAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetHPAttribute())
	{
		OnHPChanged.Broadcast(this, OldValue, NewValue);
		if (GetHP() <= 0)
		{
			OnHPReachedZero.Broadcast();
		}
	}
	else if (Attribute == GetMaxHPAttribute())
	{
		OnHPChanged.Broadcast(this, GetHP(), GetHP());
	}
	else if (Attribute == GetTurnsAttribute())
	{
		OnTurnsChanged.Broadcast(this, OldValue, NewValue);
	}
}

void UFabulaAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Convert into -Health and then clamp
		const float DamageValue = GetDamage();
		const float OldHealthValue = GetHP();
		const float MaxHealthValue = GetMaxHP();
		const float NewHealthValue = FMath::Clamp(OldHealthValue - DamageValue, 0.0f, MaxHealthValue);

		if (OldHealthValue != NewHealthValue)
		{
			// Set the new health after clamping to min-max
			SetHP(NewHealthValue);
		}

		// Clear the meta attribute that temporarily held damage
		SetDamage(0.0f);
	}
}