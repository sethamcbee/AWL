// Copyright of Wet Blanket Studios


#include "Date.h"

#include "Containers/UnrealString.h" 


int HourLengthMinutes = 60;
int DayLengthHours = 24;
int SeasonLengthDays = 10;
int YearLengthSeasons = 4;

int MinuteLengthTicks = 60;
int HourLengthTicks = MinuteLengthTicks * HourLengthMinutes;
int DayLengthTicks = HourLengthTicks * DayLengthHours;
int SeasonLengthTicks = DayLengthTicks * SeasonLengthDays;
int YearLengthTicks = SeasonLengthTicks * YearLengthSeasons;

int YearLengthDays = YearLengthTicks / DayLengthTicks;

int BabyLengthYears = 1;
int ToddlerLengthYears = 1;
int ChildLengthYears = 2;
int TeenLengthYears = 2;
int AdultLengthYears = 8;
int SeniorLengthYears = 3;

int BabyAgeYears = 0;
int ToddlerAgeYears = BabyAgeYears + BabyLengthYears;
int ChildAgeYears = ToddlerAgeYears + ToddlerLengthYears;
int TeenAgeYears = ChildAgeYears + ChildLengthYears;
int AdultAgeYears = TeenAgeYears + TeenLengthYears;
int SeniorAgeYears = AdultAgeYears + AdultLengthYears;
int DeathAgeYears = SeniorAgeYears + SeniorLengthYears;

int BabyAgeTicks = BabyAgeYears * YearLengthTicks;
int ToddlerAgeTicks = ToddlerAgeYears * YearLengthTicks;
int ChildAgeTicks = ChildAgeYears * YearLengthTicks;
int TeenAgeTicks = TeenAgeYears * YearLengthTicks;
int AdultAgeTicks = AdultAgeYears * YearLengthTicks;
int SeniorAgeTicks = SeniorAgeYears * YearLengthTicks;
int DeathAgeTicks = DeathAgeYears * YearLengthTicks;


int TicksToMinutes(int Ticks)
{
    return Ticks / MinuteLengthTicks;
}


int TicksToHours(int Ticks)
{
    return Ticks / HourLengthTicks;
}


int TicksToDays(int Ticks)
{
    return Ticks / DayLengthTicks;
}


int TicksToSeasons(int Ticks)
{
    return Ticks / SeasonLengthTicks;
}


int TicksToYears(int Ticks)
{
    return Ticks / YearLengthTicks;
}


int MinutesToTicks(int Minutes)
{
    return Minutes * MinuteLengthTicks;
}


int HoursToTicks(int Hours)
{
    return Hours * HourLengthTicks;
}


int DaysToTicks(int Days)
{
    return Days * DayLengthTicks;
}


int SeasonsToTicks(int Seasons)
{
    return Seasons * SeasonLengthTicks;
}


int YearsToTicks(int Years)
{
    return Years * YearLengthTicks;
}


int YearsToDays(int Years)
{
    int Ticks = YearsToTicks(Years);
    return TicksToDays(Ticks);
}


int RandBabyAge(FAWLRand& Rng)
{
    int Min = BabyAgeYears;
    int Max = ToddlerAgeYears - 1;
    return Rng(Min, Max);
}


int RandToddlerAge(FAWLRand& Rng)
{
    int Min = ToddlerAgeYears;
    int Max = ChildAgeYears - 1;
    return Rng(Min, Max);
}


int RandChildAge(FAWLRand& Rng)
{
    int Min = ChildAgeYears;
    int Max = TeenAgeYears - 1;
    return Rng(Min, Max);
}


int RandTeenAge(FAWLRand& Rng)
{
    int Min = TeenAgeYears;
    int Max = AdultAgeYears - 1;
    return Rng(Min, Max);
}


int RandAdultAge(FAWLRand& Rng)
{
    int Min = AdultAgeYears;
    int Max = SeniorAgeYears - 1;
    return Rng(Min, Max);
}


int RandSeniorAge(FAWLRand& Rng)
{
    int Min = SeniorAgeYears;
    int Max = DeathAgeYears - 1;
    return Rng(Min, Max);
}


int RandBirthday(FAWLRand& Rng)
{
    int Min = 0;
    int MaxTicks = YearLengthTicks - 1;
    int Max = TicksToDays(MaxTicks);
    return Rng(Min, Max);
}


FString BirthdayToString(int Birthday)
{
    int SeasonN = Birthday / SeasonLengthDays;
    FString Ret;
    if (SeasonN == 0)
    {
        Ret = "Spring ";
    }
    else if (SeasonN == 1)
    {
        Ret = "Summer ";
    }
    else if (SeasonN == 2)
    {
        Ret = "Fall ";
    }
    else if (SeasonN == 3)
    {
        Ret = "Winter ";
    }

    int Ticks = DaysToTicks(Birthday);
    int SeasonTicks = SeasonLengthTicks * SeasonN;
    int DayTicks = Ticks - SeasonTicks;
    int Day = TicksToDays(DayTicks) + 1;

    return Ret + FString::FromInt(Day);
}