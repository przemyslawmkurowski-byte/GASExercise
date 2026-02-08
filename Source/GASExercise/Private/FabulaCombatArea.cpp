// Fill out your copyright notice in the Description page of Project Settings.


#include "FabulaCombatArea.h"

// Sets default values
AFabulaCombatArea::AFabulaCombatArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFabulaCombatArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFabulaCombatArea::Tick(float DeltaTime)
{
	// should never tick
	Super::Tick(DeltaTime);

}

