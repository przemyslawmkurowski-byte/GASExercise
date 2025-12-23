#pragma once

#include "CoreMinimal.h"
#include "JRPGAbilitySystemComponent.h"
#include "JRPGActionSignature.generated.h"

/*
 * Basic data structure representing do-able action. Format: Who do What (with Which optional params) against Who.
 */
USTRUCT(BlueprintType)
struct FJRPGActionSignature
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	UJRPGAbilitySystemComponent* Self = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UGameplayAbility* Ability = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<UJRPGAbilitySystemComponent*> Targets;
};
