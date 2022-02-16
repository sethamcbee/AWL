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
	Minute = 0;
	Hour = 0;
	Day = 1;
	Season = ESeason::Spring;
	Year = 1;
	TOD = 0;
}


// Called when the game starts
void UTimeManager::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.SetTickFunctionEnable(false);

	UpdateMinutes.Broadcast(Minute);
	UpdateHours.Broadcast(Hour);
	UpdateDays.Broadcast(Day);
	UpdateSeasons.Broadcast(Season);
	UpdateYears.Broadcast(Year);
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
	UpdateClocks();

	++Ticks;

	if (bUpdateSun)
	{
		float SunPitch = 75.0 + (360.0 * TOD) / (float)DayLengthTicks;
		FRotator NewRotation = FRotator(SunPitch, 0, 0.0);

		FQuat QuatRotation = FQuat(NewRotation);

		Sun->SetActorRotation(QuatRotation);
	}
}


void UTimeManager::UpdateClocks()
{
	++TOD;
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
}


void UTimeManager::ForceUpdateClocks()
{
	UpdateMinutes.Broadcast(Minute);
	UpdateHours.Broadcast(Hour);
	UpdateDays.Broadcast(Day);
	UpdateSeasons.Broadcast(Season);
	UpdateYears.Broadcast(Year);
}