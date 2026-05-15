// Fill out your copyright notice in the Description page of Project Settings.

#include "CreatureCardWidget.h"

void UCreatureCardWidget::BindToCreature(UFabulaAbilitySystemComponent* InComp, UFabulaAttributeSet* InAttributes)
{
	InAttributes->OnHPChanged.AddDynamic(this, &UCreatureCardWidget::RefreshHP);
	InAttributes->OnMPChanged.AddDynamic(this, &UCreatureCardWidget::RefreshMP);
	InAttributes->OnIPChanged.AddDynamic(this, &UCreatureCardWidget::RefreshIP);
	InAttributes->OnTurnsChanged.AddDynamic(this, &UCreatureCardWidget::RefreshTurns);

	FGameplayTag Protected = FGameplayTag::RequestGameplayTag(FName("Fabula.Status.Protected.Guard"));

	InComp->RegisterGameplayTagEvent(Protected,
		EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UCreatureCardWidget::OnProtectionStatusChanged);

	// first refresh
	RefreshHP(InAttributes, InAttributes->GetHP(), InAttributes->GetHP());
	RefreshMP(InAttributes, InAttributes->GetMP(), InAttributes->GetMP());
	RefreshIP(InAttributes, InAttributes->GetIP(), InAttributes->GetIP());
	RefreshTurns(InAttributes, InAttributes->GetTurns(), InAttributes->GetTurns());
	OnProtectionStatusChanged(Protected, InComp->GetTagCount(Protected));
		//InAttributes->GetHP(), InAttributes->GetHP());

	CachedComponent = InComp;
	CachedAttributeSet = InAttributes;
}