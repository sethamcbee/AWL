// Copyright of Wet Blanket Studios

#pragma once

#include "AWLRand.h"
#include "Lot.h"
#include "TimeManager.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AWLGameState.generated.h"

const int LOT_COUNT = 30;
const int LOTS_OCCUPIED = 15;

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

	void Generate();

	FString RandMaleName(FAWLRand& Rng);
	FString RandFemaleName(FAWLRand& Rng);

	UPROPERTY(VisibleInstanceOnly)
	TSet<FString> MaleNames;

	UPROPERTY(VisibleInstanceOnly)
	TSet<FString> FemaleNames;

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