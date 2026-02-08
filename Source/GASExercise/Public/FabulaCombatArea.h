// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FabulaCombatArea.generated.h"

/*
* Actor representing single Encounter. When combat starts, Characters from both Parties take positions defined by Encounter;
*/
UCLASS()
class GASEXERCISE_API AFabulaCombatArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFabulaCombatArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	TArray<USceneComponent*> GetCombatPositionsForParty0();

	UFUNCTION(BlueprintImplementableEvent)
	TArray<USceneComponent*> GetCombatPositionsForParty1();

};
