// Fill out your copyright notice in the Description page of Project Settings.

#include "JRPGAttributeSet.h"

#include "GameplayEffectExtension.h"

UJRPGAttributeSet::UJRPGAttributeSet()
{
	InitLevel(5);
	InitHP(70);
	InitMaxHP(70);
}

void UJRPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHP());
	}

	Super::PreAttributeChange(Attribute, NewValue);
}

void UJRPGAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetHPAttribute())
	{
		OnHPChanged.Broadcast(this, OldValue, NewValue);
	}
	else if (Attribute == GetMaxHPAttribute())
	{
		OnHPChanged.Broadcast(this, GetHP(), GetHP());
	}
}

void UJRPGAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
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