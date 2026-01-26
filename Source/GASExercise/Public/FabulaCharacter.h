// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "FabulaAbilitySystemComponent.h"
#include "FabulaAttributeSet.h"
#include "FabulaCharacter.generated.h"

class AFabulaParty;

/*
* Simple Character that compose UFabulaAbilitySystemComponent and UFabulaAttributeSet.
* Note this class is not cooperating with whole Fabula system (this is UFabulaAbilitySystemComponent responsibility).
*/

UCLASS()
class GASEXERCISE_API AFabulaCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UFabulaAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	const UFabulaAttributeSet* AttributeSet = nullptr;

public:
	// Sets default values for this character's properties
	AFabulaCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UFabulaAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComp; }

	UFUNCTION(BlueprintImplementableEvent)
	void OnRoundStarted();
};
