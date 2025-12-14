// Fill out your copyright notice in the Description page of Project Settings.


#include "JRPGCharacter.h"

// Sets default values
AJRPGCharacter::AJRPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UJRPGAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UJRPGAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void AJRPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJRPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJRPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

