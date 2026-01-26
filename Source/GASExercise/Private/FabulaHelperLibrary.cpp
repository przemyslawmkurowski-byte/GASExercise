// Fill out your copyright notice in the Description page of Project Settings.


#include "FabulaHelperLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilityTask_FabulaTargetting.h"
#include "FabulaAbilitySystemComponent.h"
#include "FabulaCharacter.h"
#include "FabulaCombatSubsystem.h"
#include "FabulaParty.h"

void UFabulaHelperLibrary::BasicRoll(UAbilitySystemComponent* InCreature, FGameplayAttribute InAttribute0, FGameplayAttribute InAttribute1,
	int InModifier, int& OutResult, int& OutHighRoll, ERollSpecialResult& OutSpecialResult)
{
	bool fake;

	const int Attr0 = InCreature->GetGameplayAttributeValue(InAttribute0, fake);
	const int Attr1 = InCreature->GetGameplayAttributeValue(InAttribute1, fake);

	const int Roll0 = FMath::RandRange(1, Attr0);
	const int Roll1 = FMath::RandRange(1, Attr1);

	OutHighRoll = Roll0 > Roll1 ? Roll0 : Roll1;
	OutResult = Roll0 + Roll1 + InModifier;

	if (Roll0 == Roll1 && Roll0 == 1)
		OutSpecialResult = ERollSpecialResult::Fumble;
	else if (Roll0 == Roll1 && Roll0 > 5) // sic! critical success happens only on dublets of 6, 7, 8 etc
		OutSpecialResult = ERollSpecialResult::CriticalSuccess;
	else
		OutSpecialResult = ERollSpecialResult::None;
}

TArray<UFabulaAbilitySystemComponent*> UFabulaHelperLibrary::GetAvailableTargets(UFabulaCombatSubsystem* InContext,
	UFabulaAbilitySystemComponent* InCaller,
	ETargetType InTargetType,
	bool InAllowTargettingDeadCreatures)
{
	TArray<UFabulaAbilitySystemComponent*> Ret; 
	switch (InTargetType)
	{
		case ETargetType::ETT_Self:
		{
			Ret.Add(InCaller);
			break;
		}
		case ETargetType::ETT_Ally:
		{
			AFabulaParty* Party = InCaller->GetParty();
			Ret = Party->GetAllCreatures();
			Ret.Remove(InCaller);
			break;
		}
		case ETargetType::ETT_SelfOrAlly:
		{
			AFabulaParty* Party = InCaller->GetParty();
			Ret = Party->GetAllCreatures();
			break;
		}
		case ETargetType::ETT_Enemy:
		{
			AFabulaParty* Party = InContext->GetOpposingParty(InCaller);
			Ret = Party->GetAllCreatures();
			break;
		}
		case ETargetType::ETT_Any:
		default:
		{
			AFabulaParty* OpposingParty = InContext->GetOpposingParty(InCaller);
			Ret = OpposingParty->GetAllCreatures();
			AFabulaParty* Party = InCaller->GetParty();
			TArray<UFabulaAbilitySystemComponent*> Allies = Party->GetAllCreatures();
			Ret.Append(Allies);
			break;
		}
	}

	if (!InAllowTargettingDeadCreatures)
	{
		for (int i = Ret.Num() - 1; i >= 0; --i)
		{
			if (Ret[i]->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Fabula.Status.Dead"))))
			{
				// Note we cannot use RemoveAtSwap, because order matter.
				Ret.RemoveAt(i);
			}
		}
	}

	return Ret;
}