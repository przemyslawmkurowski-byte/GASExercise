// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalActorSubsystem.h"

void UGlobalActorSubsystem::SetPlayerParty(AFabulaParty* InParty)
{
	PlayerParty = InParty;
}

AFabulaParty* UGlobalActorSubsystem::GetPlayerParty()
{
	return PlayerParty;
}