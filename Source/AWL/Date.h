// Copyright of Wet Blanket Studios

#pragma once

#include "AWLRand.h"

#include "CoreMinimal.h"

UENUM()
enum class ELifeStage : uint8
{
	Baby UMETA(DisplayName = "Baby"),
	Toddler UMETA(DisplayName = "Toddler"),
	Child UMETA(DisplayName = "Child"),
	Teen UMETA(DisplayName = "Teen"),
	Adult UMETA(DisplayName = "Adult"),
	Senior UMETA(DisplayName = "Senior"),
	Dead UMETA(DisplayName = "Dead")
};

UENUM()
enum class ESeason : uint8
{
	Spring UMETA(DisplayName = "Spring"),
	Summer UMETA(DisplayName = "Summer"),
	Fall UMETA(DisplayName = "Fall"),
	Winter UMETA(DisplayName = "Winter")
};

 // Time and date rates.
extern int HourLengthMinutes;
extern int DayLengthHours;
extern int SeasonLengthDays;
extern int YearLengthSeasons;

extern int MinuteLengthTicks;
extern int HourLengthTicks;
extern int DayLengthTicks;
extern int SeasonLengthTicks;
extern int YearLengthTicks;

extern int YearLengthDays;

// Aging.
extern int BabyLengthYears;
extern int ToddlerLengthYears;
extern int ChildLengthYears;
extern int TeenLengthYears;
extern int AdultLengthYears;
extern int SeniorLengthYears;

extern int BabyAgeYears;
extern int ToddlerAgeYears;
extern int ChildAgeYears;
extern int TeenAgeYears;
extern int AdultAgeYears;
extern int SeniorAgeYears;
extern int DeathAgeYears;

extern int BabyAgeTicks;
extern int ToddlerAgeTicks;
extern int ChildAgeTicks;
extern int TeenAgeTicks;
extern int AdultAgeTicks;
extern int SeniorAgeTicks;
extern int DeathAgeTicks;

// Time and date conversions.
int TicksToMinutes(int Ticks);
int TicksToHours(int Ticks);
int TicksToDays(int Ticks);
int TicksToSeasons(int Ticks);
int TicksToYears(int Ticks);

int MinutesToTicks(int Minutes);
int HoursToTicks(int Hours);
int DaysToTicks(int Days);
int SeasonsToTicks(int Seasons);
int YearsToTicks(int Years);

int YearsToDays(int Years);

// Character generation.
int RandBabyAge(FAWLRand& Rng);
int RandToddlerAge(FAWLRand& Rng);
int RandChildAge(FAWLRand& Rng);
int RandTeenAge(FAWLRand& Rng);
int RandAdultAge(FAWLRand& Rng);
int RandSeniorAge(FAWLRand& Rng);

FString SeasonToString(ESeason Season);
ELifeStage YearsToLifeStage(int Years);
int RandBirthday(FAWLRand& Rng);
FString BirthdayToString(int Birthday);