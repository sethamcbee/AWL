// Copyright of Wet Blanket Studios

#pragma once

#include <random>

#include "CoreMinimal.h"

/**
 * 
 */
class AWL_API FAWLRand
{
public:
	FAWLRand();
	~FAWLRand();

	FAWLRand(int64 Seed);

	uint64 operator()();

	int64 operator()(int64 Min, int64 Max);

	uint64 Peek();

	// Generate number whose probability of being near the middle
	// of the range increases as N increases.
	int64 Avg(int64 Min, int64 Max, int N);

	bool Try(float Chance);

private:
	std::minstd_rand State;
};

extern FAWLRand GetRand;