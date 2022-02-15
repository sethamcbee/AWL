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

	UPROPERTY(EditInstanceOnly)
	TSet<FString> MaleNames;

	UPROPERTY(EditInstanceOnly)
	TSet<FString> FemaleNames;

	UPROPERTY(EditInstanceOnly)
	bool bTimeTick = false;

	UPROPERTY(EditInstanceOnly)
	UTimeManager* TimeManager;

	UPROPERTY(EditInstanceOnly)
	uint64 WorldSeed;

	FAWLRand WorldRand;
	
	UPROPERTY(EditInstanceOnly)
	TArray<ALot*> Lots;
};