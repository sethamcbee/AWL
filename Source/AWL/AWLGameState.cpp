// Copyright of Wet Blanket Studios


#include "AWLGameState.h"

#include "FSexp.h"

#include <fstream>

#include "Engine/EngineTypes.h" 
#include "Misc/MessageDialog.h"


const int LOT_COUNT = 20;
const int LOTS_OCCUPIED = 15;


static auto RandLotIndex(FAWLRand& Rng)
{
	return Rng(0, LOT_COUNT - 1);
}


AAWLGameState::AAWLGameState() : WorldSeed(1), WorldRand(WorldSeed)
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize managers.
	TimeManager = CreateDefaultSubobject<UTimeManager>("UTimeManager");

	// Initialize lots.
	Lots.Init(nullptr, LOT_COUNT);
}


void AAWLGameState::BeginPlay()
{
	Super::BeginPlay();

	LoadModules();

	Generate();
}


void AAWLGameState::Tick(float DeltaTime)
{
	if (bTimeTick)
	{
		TimeManager->Update(DeltaTime);
	}
}


void AAWLGameState::LoadModules()
{
	FSexp MaleNamesSexp("C://AWLData/male_names.txt");
	auto MaleNamesList = ArrayFromSexp(MaleNamesSexp);
	for (const auto& Name : MaleNamesList)
	{
		FreeMaleNames.Add(SymbolFromSexp(Name));
	}

	FSexp FemaleNamesSexp("C://AWLData/female_names.txt");
	auto FemaleNamesList = ArrayFromSexp(FemaleNamesSexp);
	for (const auto& Name : FemaleNamesList)
	{
		FreeFemaleNames.Add(SymbolFromSexp(Name));
	}
}


void AAWLGameState::Generate()
{
	// Fill random lots with occupants.
	for (size_t I = LOTS_OCCUPIED; I > 0; --I)
	{
		auto LotId = RandLotIndex(WorldRand);
		ALot* Lot = Lots[LotId];
		if (!Lot)
		{
			Lots[LotId] = GenerateLot(GetWorld(), WorldRand);
		}
		else
		{
			// Lot occupied; pick another lot.
			++I;
		}
	}

	// Generate empty lots for remaining slots.
	for (ALot* Lot : Lots)
	{
		if (!IsValid(Lot))
		{
			Lot = GenerateEmptyLot(GetWorld(), WorldRand);
		}
	}
}


FString AAWLGameState::RandMaleName(FAWLRand& Rng)
{
	auto Pred = [](const FString& A, const FString& B)
	{
		return A < B;
	};
	FreeMaleNames.Sort(Pred);
	auto Max = FreeMaleNames.Num() - 1;
	auto Index = Rng(0, Max);
	auto It = FreeMaleNames.CreateIterator();
	while (Index > 0)
	{
		--Index;
		++It;
	}
	auto Name = *It;
	FreeMaleNames.Remove(Name);
	return Name;
}

FString AAWLGameState::RandFemaleName(FAWLRand& Rng)
{
	auto Pred = [](const FString& A, const FString& B)
	{
		return A < B;
	};
	FreeFemaleNames.Sort(Pred);
	auto Max = FreeFemaleNames.Num() - 1;
	auto Index = Rng(0, Max);
	auto It = FreeFemaleNames.CreateIterator();
	while (Index > 0)
	{
		--Index;
		++It;
	}
	auto Name = *It;
	FreeFemaleNames.Remove(Name);
	return Name;
}