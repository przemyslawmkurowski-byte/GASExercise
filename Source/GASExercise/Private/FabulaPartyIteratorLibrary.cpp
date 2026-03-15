// Fill out your copyright notice in the Description page of Project Settings.


#include "FabulaPartyIteratorLibrary.h"

#include "FabulaAbilitySystemComponent.h"
#include "FabulaParty.h"


UFabulaAbilitySystemComponent* FFabulaPartyIterator::TryGetCurrent()
{
	AFabulaParty* Locked = Party.Get();
	if (Locked == nullptr)
		return nullptr;

	if (CurrentIndex == -1)
		return nullptr;

	int NumOfCreatures = Locked->GetAllCreatures().Num();
	if (CurrentIndex >= NumOfCreatures)
		return nullptr;

	return Locked->GetAllCreatures()[CurrentIndex];
}

UFabulaAbilitySystemComponent* FFabulaPartyIterator::Next()
{
	/* Sister function: Prev */
	AFabulaParty* Locked = Party.Get();
	if (Locked == nullptr)
		return nullptr;
	auto Creatures = Locked->GetAllCreatures();
	int Length = Creatures.Num();

	// used to detect infinite loops
	int StartIndex = CurrentIndex;

	for (++CurrentIndex; CurrentIndex != StartIndex; ++CurrentIndex)
	{
		if (CurrentIndex >= Length)
		{
			if (Policies.bCircular == true)
			{
				CurrentIndex = 0;
			}
			else
			{
				CurrentIndex = Length - 1;
				StartIndex = Length;// HACK! to force loop stop next iteration
			}
		}

		UFabulaAbilitySystemComponent* Candidate = Creatures[CurrentIndex];
		if (!ShouldBeSkipped(Candidate))
				return Candidate;
	}
	return nullptr;
}

UFabulaAbilitySystemComponent* FFabulaPartyIterator::Prev()
{
	/* Sister function: Next */
	AFabulaParty* Locked = Party.Get();
	if (Locked == nullptr)
		return nullptr;
	auto Creatures = Locked->GetAllCreatures();
	int Length = Creatures.Num();

	// used to detect infinite loops
	int StartIndex = CurrentIndex;

	for (--CurrentIndex; CurrentIndex != StartIndex; --CurrentIndex)
	{
		if (CurrentIndex < 0)
		{
			if (Policies.bCircular == true)
			{
				CurrentIndex = Length - 1;
			}
			else
			{
				CurrentIndex = 0;
				StartIndex = -1;// HACK! to force loop stop next iteration
			}
		}

		UFabulaAbilitySystemComponent* Candidate = Creatures[CurrentIndex];
		if (!ShouldBeSkipped(Candidate))
			return Candidate;
	}
	return nullptr;
}

bool FFabulaPartyIterator::ShouldBeSkipped(UFabulaAbilitySystemComponent* InCandidate)
{
	if (InCandidate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Detected nullptr, in Party->Creatures, at index %i"), CurrentIndex);
		return true;
	}

	if (Policies.bSkipDead && !InCandidate->IsAlive())
		return true;

	return false;
}

UFabulaAbilitySystemComponent* UFabulaPartyIteratorLibrary::TryGetCurrent(UPARAM(ref) FFabulaPartyIterator& InIterator)
{
	return InIterator.TryGetCurrent();
}

TArray<UFabulaAbilitySystemComponent*> UFabulaPartyIteratorLibrary::TryGetCurrentAsArray(UPARAM(ref) FFabulaPartyIterator& InIterator)
{
	UFabulaAbilitySystemComponent* Current = InIterator.TryGetCurrent();
	return Current != nullptr 
		? TArray<UFabulaAbilitySystemComponent*>({ Current }) 
		: TArray< UFabulaAbilitySystemComponent*>();
}

UFabulaAbilitySystemComponent* UFabulaPartyIteratorLibrary::Next(UPARAM(ref) FFabulaPartyIterator& InIterator)
{
	return InIterator.Next();
}

UFabulaAbilitySystemComponent* UFabulaPartyIteratorLibrary::Prev(UPARAM(ref) FFabulaPartyIterator& InIterator)
{
	return InIterator.Prev();
}