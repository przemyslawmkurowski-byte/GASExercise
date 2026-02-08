// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "FabulaAttributeSet.h"
#include "FabulaAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "FabulaPlayerCharacter.generated.h"

UCLASS()
class GASEXERCISE_API AFabulaPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UFabulaAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	const UFabulaAttributeSet* AttributeSet = nullptr;

public:
	// Sets default values for this character's properties
	AFabulaPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
