// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "JRPGAbilitySystemComponent.h"
#include "JRPGAttributeSet.h"
#include "JRPGCharacter.generated.h"

UCLASS()
class GASEXERCISE_API AJRPGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UJRPGAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	const UJRPGAttributeSet* AttributeSet = nullptr;

public:
	// Sets default values for this character's properties
	AJRPGCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UJRPGAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComp; }

};
