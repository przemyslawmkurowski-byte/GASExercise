// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FabulaPartyIteratorLibrary.generated.h"

class UFabulaAbilitySystemComponent;

/*
* This file is one big complex of structs and classes that have only one job - decrease number of nodes I need to spend to iterate over selectable targets.
*/

/*
* How Iterator should handle non-obvious cases
*/
USTRUCT(BlueprintType)
struct GASEXERCISE_API FFabulaPartyIteratorPolicy
{
	GENERATED_BODY()

	/* How Iterator should behave when trying to access LastElement->Next (or FirstElement->Prev). True - go to first element; false - stay where you are */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCircular = false;

	/*  Should iterator skip over dead bodies */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bSkipDead = true;
};


/* Wrapper over AFabulaParty. Its job is to cache Current, and define functions accessible through library */
USTRUCT(BlueprintType)
struct GASEXERCISE_API FFabulaPartyIterator
{
	GENERATED_BODY()

	friend class AFabulaParty;

public:
	FFabulaPartyIterator() : Party(nullptr), Policies(FFabulaPartyIteratorPolicy()) {}

	FFabulaPartyIterator(AFabulaParty* InIterateOver, FFabulaPartyIteratorPolicy InPolicies = FFabulaPartyIteratorPolicy())
		: Party(InIterateOver), Policies(InPolicies) {	}


	/* ATTENTION: it is not guaranteed how this function will work with policies */
	UFabulaAbilitySystemComponent* TryGetCurrent();
	UFabulaAbilitySystemComponent* Next();
	UFabulaAbilitySystemComponent* Prev();

private:
	bool ShouldBeSkipped(UFabulaAbilitySystemComponent* InCandidate);

	TWeakObjectPtr<AFabulaParty> Party = nullptr;
	int CurrentIndex = 0;

	FFabulaPartyIteratorPolicy Policies;
};

/**
 * FStruct cannot declare BlueprintCallable functions, so we need static function library
 */
UCLASS()
class GASEXERCISE_API UFabulaPartyIteratorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UFabulaAbilitySystemComponent* TryGetCurrent(UPARAM(ref) FFabulaPartyIterator& InIterator);

	UFUNCTION(BlueprintCallable)
	static UFabulaAbilitySystemComponent* Next(UPARAM(ref) FFabulaPartyIterator& InIterator);

	UFUNCTION(BlueprintCallable)
	static UFabulaAbilitySystemComponent* Prev(UPARAM(ref) FFabulaPartyIterator& InIterator);
	
};
