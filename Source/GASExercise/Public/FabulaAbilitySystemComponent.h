// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "FabulaAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundStarted);

class AFabulaParty;

/**
 * Object that represent single Creature in all Fabula systems.
 */
UCLASS()
class GASEXERCISE_API UFabulaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetParty(AFabulaParty* InParty);

	bool HasTurns();
	AFabulaParty* GetParty();

	UPROPERTY(BlueprintAssignable)
	FOnRoundStarted OnRoundStarted;


private:
	/* Because basic params are GameplayEffect in GAS, it seems */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> InitData;

	/* Will be automatially set by FabulaParty */
	UPROPERTY(VisibleAnywhere)
	AFabulaParty* Party;
	
};
