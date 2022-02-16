// Copyright of Wet Blanket Studios


#include "AWLGameState.h"

#include "Figure/Lexer.h"
#include "Figure/Sexp.h"

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
#if 1
	// Load male names.
	TArray<FString> MaleNamesTmp;
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FString MaleNamesFile = TEXT("C://AWLData/male_names.txt");
	if (FileManager.FileExists(*MaleNamesFile))
	{
		FFileHelper::LoadFileToStringArray(MaleNamesTmp, *MaleNamesFile, FFileHelper::EHashOptions::None);
	}
	for (const auto& Name : MaleNamesTmp)
	{
		MaleNames.Add(Name);
	}

	// Load female names.
	TArray<FString> FemaleNamesTmp;
	FString FemaleNamesFile = TEXT("C://AWLData/female_names.txt");
	if (FileManager.FileExists(*FemaleNamesFile))
	{
		FFileHelper::LoadFileToStringArray(FemaleNamesTmp, *FemaleNamesFile, FFileHelper::EHashOptions::None);
	}
	for (const auto& Name : FemaleNamesTmp)
	{
		FemaleNames.Add(Name);
	}
#endif

	auto MaleNamesModule = std::ifstream(TEXT("C://AWLData/male_names.txt"));
	auto MaleNamesLexer = Figure::Lexer(MaleNamesModule);
	auto MaleNamesSexp = Figure::Sexp(MaleNamesLexer);
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
	MaleNames.Sort(Pred);
	auto Max = MaleNames.Num() - 1;
	auto Index = Rng(0, Max);
	auto It = MaleNames.CreateIterator();
	while (Index > 0)
	{
		--Index;
		++It;
	}
	auto Name = *It;
	MaleNames.Remove(Name);
	return Name;
}

FString AAWLGameState::RandFemaleName(FAWLRand& Rng)
{
	auto Pred = [](const FString& A, const FString& B)
	{
		return A < B;
	};
	FemaleNames.Sort(Pred);
	auto Max = FemaleNames.Num() - 1;
	auto Index = Rng(0, Max);
	auto It = FemaleNames.CreateIterator();
	while (Index > 0)
	{
		--Index;
		++It;
	}
	auto Name = *It;
	FemaleNames.Remove(Name);
	return Name;
}