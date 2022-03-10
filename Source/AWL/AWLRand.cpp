// Copyright of Wet Blanket Studios

#include "AWLRand.h"

#include <cstdlib>
#include <random>

using GeneratorType = std::minstd_rand;

FAWLRand GetRand(time(NULL));
const int RandMax = GeneratorType::max();

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
	return LCG();
}

int64 FAWLRand::operator()(int64 Min, int64 Max)
{
	auto Range = Max - Min + 1;
	auto R = LCG();
	return R / (RandMax / Range + 1) + Min;
}

uint64 FAWLRand::Peek()
{
	return State;
}

uint64 FAWLRand::LCG()
{
	GeneratorType Generator{ (unsigned int) State };
	State = (uint64) Generator();
	return State;
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