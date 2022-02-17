// Copyright of Wet Blanket Studios

#pragma once

#include "AWLRand.h"
#include "Lot.h"
#include "TimeManager.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AWLGameState.generated.h"

extern const int LOT_COUNT;
extern const int LOTS_OCCUPIED;

/**
 * 
 */
UCLASS()
class AWL_API AAWLGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	AAWLGameState();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void LoadModules();

	void Generate();

	FString RandMaleName(FAWLRand& Rng);
	FString RandFemaleName(FAWLRand& Rng);

	UPROPERTY(VisibleInstanceOnly)
	TArray<FString> MaleNames;

	UPROPERTY(VisibleInstanceOnly)
	TArray<FString> FemaleNames;

	UPROPERTY(VisibleInstanceOnly)
	TSet<FString> FreeMaleNames;

	UPROPERTY(VisibleInstanceOnly)
	TSet<FString> FreeFemaleNames;

	UPROPERTY(VisibleInstanceOnly)
	bool bTimeTick = false;

	UPROPERTY(VisibleInstanceOnly)
	UTimeManager* TimeManager;

	UPROPERTY(VisibleInstanceOnly)
	uint64 WorldSeed;

	FAWLRand WorldRand;
	
	UPROPERTY(VisibleInstanceOnly)
	TArray<ALot*> Lots;
};