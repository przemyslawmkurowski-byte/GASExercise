// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "JRPGAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Attribute set is mathematical and GameplayAbilitySystem-affiliated description of Creature.
 */
UCLASS()
class GASEXERCISE_API UJRPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UJRPGAttributeSet();

protected:
	/* Creature Level */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Level;

	/*
 * Core attributes are described as dice: d6, d8, d10 or d12. Current value of any dice can not be smaller than d6,
 * and only in very special circumstances not included in this exercise can be bigger than d12.
 */

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData DexterityDice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData InsightDice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MightDice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData WillpowerDice;*/

	/* Health points. How much damage it takes to knoch off Creature */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHP;

	/* Magic points. Used to cast spells and use some paramagic abilities. /
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxMP;

	/ Equipment points. Used for Equpment action. /
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData EP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxEP;*/


public:


	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, Level);

	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, HP);
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, MaxHP);






	
};
