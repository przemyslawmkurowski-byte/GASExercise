// Fill out your copyright notice in the Description page of Project Settings.

#include "FabulaPlayerCharacter.h"

#include "Components/CapsuleComponent.h"

// Sets default values
AFabulaPlayerCharacter::AFabulaPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	//SpringArm->TargetArmLength = 400;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm);


	AbilitySystemComp = CreateDefaultSubobject<UFabulaAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UFabulaAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void AFabulaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFabulaPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFabulaPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

