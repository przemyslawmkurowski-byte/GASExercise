// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FabulaAbilitySystemComponent.h"
#include "FabulaAttributeSet.h"
#include "CreatureCardWidget.generated.h"

/**
 * Code-side interface for communication between FabulaAttributeSet/FabulaAbilitySystemComponent, and in-game widget. Used to free blueprint from binding itself to events
 */
UCLASS()
class GASEXERCISE_API UCreatureCardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void BindToCreature(UFabulaAbilitySystemComponent* InComp, UFabulaAttributeSet* InAttributes);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void RefreshHP(UFabulaAttributeSet* InAttributeSet, float InOldValue, float InNewValue);
	
	UFUNCTION(BlueprintImplementableEvent)
	void RefreshMP(UFabulaAttributeSet* InAttributeSet, float InOldValue, float InNewValue);
	
	UFUNCTION(BlueprintImplementableEvent)
    void RefreshIP(UFabulaAttributeSet* InAttributeSet, float InOldValue, float InNewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void RefreshTurns(UFabulaAttributeSet* InAttributeSet, float InOldValue, float InNewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnProtectionStatusChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly)
	UFabulaAbilitySystemComponent* CachedComponent;

	UPROPERTY(BlueprintReadOnly)
	UFabulaAttributeSet* CachedAttributeSet;
};
