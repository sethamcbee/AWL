// Copyright of Wet Blanket Studios


#include "TimeManager.h"

#include "AWLGameState.h"
#include "Date.h"
#include "Misc/MessageDialog.h"


// Sets default values for this component's properties
UTimeManager::UTimeManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Ticks = 0;
	WorldTick = 0;
	TimeSinceLastMinute = 0.0f;
	Minute = 0;
	Hour = 0;
	Day = 1;
	Season = ESeason::Spring;
	Year = 1;
	TOD = 0.0f;
}


// Called when the game starts
void UTimeManager::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.SetTickFunctionEnable(false);

	// Set initial time.
	Hour = 6;

	ForceUpdateClocks();
}


// Called every frame
void UTimeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UTimeManager::RegisterSun(AAWLGameState* GS, AActor* Actor)
{
	GS->TimeManager->Sun = Actor;
	GS->bTimeTick = true;
	GS->TimeManager->bUpdateSun = true;
}


void UTimeManager::Update(float DeltaTime)
{
	UpdateClocks(DeltaTime);

	// Update time of day.
	TOD += DeltaTime;
	while (TOD > DayLengthSeconds)
	{
		TOD -= DayLengthSeconds;
	}

	++Ticks;

	if (bUpdateSun)
	{
		float SunPitch = 75.0 + (360.0 * TOD) / (float)DayLengthSeconds;
		FRotator NewRotation = FRotator(SunPitch, 0, 0.0f);

		FQuat QuatRotation = FQuat(NewRotation);

		Sun->SetActorRotation(QuatRotation);
	}
}


void UTimeManager::UpdateClocks(float DeltaTime)
{
	TimeSinceLastMinute += DeltaTime;
	if (TimeSinceLastMinute < MinuteLengthSeconds)
	{
		return;
	}
	++WorldTick;

	while (TimeSinceLastMinute >= MinuteLengthSeconds)
	{
		TimeSinceLastMinute -= MinuteLengthSeconds;
		++Minute;
	}

	if (Minute < HourLengthMinutes)
	{
		UpdateMinutes.Broadcast(Minute);
		return;
	}
	else
	{
		while (Minute >= HourLengthMinutes)
		{
			Minute -= HourLengthMinutes;
			++Hour;
		}
	}
	UpdateMinutes.Broadcast(Minute);

	if (Hour < DayLengthHours)
	{
		UpdateHours.Broadcast(Hour);
		return;
	}
	else
	{
		while (Hour >= DayLengthHours)
		{
			Hour -= DayLengthHours;
			++Day;
		}
	}
	UpdateHours.Broadcast(Hour);

	if (Day < SeasonLengthDays)
	{
		UpdateDays.Broadcast(Day);
		return;
	}
	else
	{
		while (Day > SeasonLengthDays)
		{
			Day -= SeasonLengthDays;

			if (Season == ESeason::Spring)
			{
				Season = ESeason::Summer;
			}
			else if (Season == ESeason::Summer)
			{
				Season = ESeason::Fall;
			}
			else if (Season == ESeason::Fall)
			{
				Season = ESeason::Winter;
			}
			else
			{
				Season = ESeason::Spring;
				++Year;
				UpdateYears.Broadcast(Year);
			}

			UpdateSeasons.Broadcast(Season);
		}
	}
	UpdateDays.Broadcast(Day);

#if 0
	if (Ticks % DayLengthTicks == 0)
	{
		TOD = 0;
	}

	if (Ticks % MinuteLengthTicks == 0)
	{
		++Minute;
	}

	if (Ticks % HourLengthTicks == 0)
	{
		Minute = 0;
		++Hour;
		UpdateMinutes.Broadcast(Minute);
	}
	else
	{
		UpdateMinutes.Broadcast(Minute);
		return;
	}

	if (Ticks % DayLengthTicks == 0)
	{
		Hour = 0;
		++Day;
		UpdateHours.Broadcast(Hour);
	}
	else
	{
		UpdateHours.Broadcast(Hour);
		return;
	}

	if (Ticks % SeasonLengthTicks == 0)
	{
		Day = 1;
		UpdateDays.Broadcast(Day);

		if (Season == ESeason::Spring)
		{
			Season = ESeason::Summer;
		}
		else if (Season == ESeason::Summer)
		{
			Season = ESeason::Fall;
		}
		else if (Season == ESeason::Fall)
		{
			Season = ESeason::Winter;
		}
		else
		{
			Season = ESeason::Spring;
			++Year;
			UpdateYears.Broadcast(Year);
		}

		UpdateSeasons.Broadcast(Season);
	}
	else
	{
		UpdateDays.Broadcast(Day);
	}
#endif
}


void UTimeManager::ForceUpdateClocks()
{
	UpdateMinutes.Broadcast(Minute);
	UpdateHours.Broadcast(Hour);
	UpdateDays.Broadcast(Day);
	UpdateSeasons.Broadcast(Season);
	UpdateYears.Broadcast(Year);

	float HourFrac = (float)Minute / HourLengthMinutes;
	TOD = ((float)Hour / DayLengthHours + HourFrac) * DayLengthSeconds;
}