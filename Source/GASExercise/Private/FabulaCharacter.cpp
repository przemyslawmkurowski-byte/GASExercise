// Fill out your copyright notice in the Description page of Project Settings.


#include "FabulaCharacter.h"
#include "FabulaParty.h"

// Sets default values
AFabulaCharacter::AFabulaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UFabulaAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UFabulaAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void AFabulaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFabulaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFabulaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}