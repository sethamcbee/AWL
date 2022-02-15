// Copyright of Wet Blanket Studios

#include "AWLRand.h"

#include <cstdlib>

FAWLRand GetRand(time(NULL));
const int RandMax = std::minstd_rand::max();

FAWLRand::FAWLRand() : State(0)
{
}

FAWLRand::~FAWLRand()
{
}

FAWLRand::FAWLRand(int64 Seed) : State(Seed)
{
}

uint64 FAWLRand::operator()()
{
	return State();
}

int64 FAWLRand::operator()(int64 Min, int64 Max)
{
	auto Range = Max - Min + 1;
	auto R = State();
	return R / (RandMax / Range + 1) + Min;
}

uint64 FAWLRand::Peek()
{
	FAWLRand& Self = *this;
	uint64 Ret = Self();
	State.seed(Ret);
	return Ret;
}

int64 FAWLRand::Avg(int64 Min, int64 Max, int N)
{
	auto& Self = *this;
	int Sum = 0;
	for (size_t I = 0; I < N; ++I)
	{
		Sum += Self(Min, Max);
	}
	return Sum / N;
}

bool FAWLRand::Try(float Chance)
{
	const int SCALE = 1000000;
	auto& Self = *this;

	int ScaledChance = (int)(Chance * (float)SCALE);
	int N = Self(0, SCALE);
	return N < ScaledChance;
}