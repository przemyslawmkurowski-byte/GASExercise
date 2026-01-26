// Fill out your copyright notice in the Description page of Project Settings.


#include "FabulaHelperLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilityTask_FabulaTargetting.h"
#include "FabulaAbilitySystemComponent.h"
#include "FabulaCharacter.h"
#include "FabulaCombatSubsystem.h"
#include "FabulaParty.h"

void UFabulaHelperLibrary::BasicCheck(UAbilitySystemComponent* Creature,
	FGameplayAttribute InAttribute0, FGameplayAttribute InAttribute1, int InDifficulty,
	bool& Success, int& HighRoll, bool& IsCritical)
{
	bool fake;

	int Attr0 = Creature->GetGameplayAttributeValue(InAttribute0, fake);
	int Attr1 = Creature->GetGameplayAttributeValue(InAttribute1, fake);

	int Roll0 = FMath::RandRange(1, Attr0);
	int Roll1 = FMath::RandRange(1, Attr1);

	HighRoll = Roll0 > Roll1 ? Roll0 : Roll1;

	// Critical success is when both dices give the same value higher than 5 (so 6 and 6, 7 and 7, 8 and 8 etc). Critical failure is when both dices give 1
	if (Roll0 == Roll1 && Roll0 == 1)
	{
		IsCritical = true;
		Success =  false;
	}
	else if (Roll0 == Roll1 && Roll0 > 5)
	{
		// critical success is a success even if rolls do not sum to InDifficulty
		IsCritical = true;
		Success =  true;
	}
	else
	{
		IsCritical = false;
		Success = Roll0 + Roll1 >= InDifficulty;
	}
}

TArray<UFabulaAbilitySystemComponent*> UFabulaHelperLibrary::GetAvailableTargets(UFabulaCombatSubsystem* Context, UFabulaAbilitySystemComponent* Caller, ETargetType TargetType)
{
	switch (TargetType)
	{
		case ETargetType::ETT_Self:
		{
			return TArray<UFabulaAbilitySystemComponent*>({ Caller });
		}
		case ETargetType::ETT_Ally:
		{
			AFabulaParty* Party = Caller->GetParty();
			TArray<UFabulaAbilitySystemComponent*> SelfParty = Party->GetAllCreatures();
			SelfParty.Remove(Caller);
			return SelfParty;
		}
		case ETargetType::ETT_SelfOrAlly:
		{
			AFabulaParty* Party = Caller->GetParty();
			TArray<UFabulaAbilitySystemComponent*> SelfParty = Party->GetAllCreatures();
			return SelfParty;
		}
		case ETargetType::ETT_Enemy:
		{
			AFabulaParty* Party = Context->GetOpposingParty(Caller);
			TArray<UFabulaAbilitySystemComponent*> OpposingParty = Party->GetAllCreatures();
			return OpposingParty;
		}
		case ETargetType::ETT_Any:
		default:
		{
			AFabulaParty* OpposingParty = Context->GetOpposingParty(Caller);
			TArray<UFabulaAbilitySystemComponent*> Ret = OpposingParty->GetAllCreatures();
			AFabulaParty* Party = Caller->GetParty();
			TArray<UFabulaAbilitySystemComponent*> Allies = Party->GetAllCreatures();
			Ret.Append(Allies);
			return Ret;
		}
	}
}