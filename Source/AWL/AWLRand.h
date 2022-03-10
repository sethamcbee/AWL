// Copyright of Wet Blanket Studios

#pragma once

#include "CoreMinimal.h"
#include "AWLRand.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAWLRand
{
	GENERATED_BODY()

	FAWLRand();
	~FAWLRand();

	FAWLRand(int64 Seed);

	uint64 operator()();

	int64 operator()(int64 Min, int64 Max);

	uint64 Peek();

	uint64 LCG();

	// Generate number whose probability of being near the middle
	// of the range increases as N increases.
	int64 Avg(int64 Min, int64 Max, int N);

	bool Try(float Chance);

	UPROPERTY(VisibleInstanceOnly)
	uint64 State;
};

extern FAWLRand GetRand;