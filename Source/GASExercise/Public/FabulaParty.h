// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FabulaParty.generated.h"

class AFabulaCharacter;
class UFabulaAbilitySystemComponent;

/*
* This is group of Creatures. Party fight together against hostile Party. It can be either PlayerParty, or singular encounter.
* Each Creature belongs to exactly one Party, and each Party is made of n Creatures (Party of 0 is technically allowed, but it would no tbe able to fight).
*/
UCLASS()
class GASEXERCISE_API AFabulaParty : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	//AFabulaParty();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/* Temporary function */
	UFUNCTION(BlueprintCallable)
	void AddCreature(UFabulaAbilitySystemComponent* InCreature);

	TArray<UFabulaAbilitySystemComponent*> GetAllCreatures();

	bool Contains(UFabulaAbilitySystemComponent* InObj);
	TArray<UFabulaAbilitySystemComponent*> GetAllCreaturesWithAtLeastOneTurn();

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

private:
	/* Is used to initialize Creatures and Creatures->SetParty in BeginPlay  */
	UPROPERTY(EditAnywhere)
	TArray<AFabulaCharacter*> CreaturesAsActors;

	UPROPERTY(VisibleAnywhere)
	TArray<UFabulaAbilitySystemComponent*> Creatures;


};
