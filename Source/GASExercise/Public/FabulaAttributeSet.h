// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "FabulaAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeChangedEvent, UAttributeSet*, AttributeSet, float, OldValue, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHPReachedZeroEvent);

/**
 * Attribute set is mathematical and GameplayAbilitySystem-affiliated description of Creature.
 */
UCLASS()
class GASEXERCISE_API UFabulaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UFabulaAttributeSet();

public:
	/* Events */
	UPROPERTY(BlueprintAssignable)
	FHPReachedZeroEvent OnHPReachedZero;


	ATTRIBUTE_ACCESSORS(UFabulaAttributeSet, TurnsPerRound);
	ATTRIBUTE_ACCESSORS(UFabulaAttributeSet, Turns);

	ATTRIBUTE_ACCESSORS(UFabulaAttributeSet, Level);

	ATTRIBUTE_ACCESSORS(UFabulaAttributeSet, DexterityDice);
	ATTRIBUTE_ACCESSORS(UFabulaAttributeSet, InsightDice);
	ATTRIBUTE_ACCESSORS(UFabulaAttributeSet, MightDice);
	ATTRIBUTE_ACCESSORS(UFabulaAttributeSet, WillpowerDice);

	ATTRIBUTE_ACCESSORS(UFabulaAttributeSet, HP);
	ATTRIBUTE_ACCESSORS(UFabulaAttributeSet, MaxHP);

	// Meta attribute set by attacking GameplayEffect. I decided to not question this approach until I finish tutorial
	UPROPERTY(VisibleAnywhere)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UFabulaAttributeSet, Damage);

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnHPChanged;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnTurnsChanged;


protected:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


protected:
	/* PCs and normal NPCs have one Turn each Round. Elite and Champion NPCs can have more. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData TurnsPerRound;

	/* PCs and normal NPCs have one Turn each Round. Elite and Champion NPCs can have more. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Turns;


	/* Creature Level */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Level;
	
	/*
	* Core attributes are described as dice: d6, d8, d10 or d12. Current value of any dice can not be smaller than d6,
	* and only in very special circumstances not included in this exercise can be bigger than d12.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData DexterityDice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData InsightDice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MightDice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData WillpowerDice;

 /* Health points. How much damage it takes to knoch off Creature */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (HideFromModifiers))
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





	
};
